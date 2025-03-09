#include "Gun.h"

#include "Transform.h"

#include "../ecs/Manager.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"


class Vector2D;

Gun::Gun() : _trPlayer(){
}

Gun::Gun(Transform* t) : _trPlayer(t), _lastShoot(0) {
}

Gun::~Gun(){
}

void Gun::reset()
{
	//Recorremos el array de balas
	for (Gun::Bullet& b : _bullets) {
		//Las "desusamos"
		b.used = false;
	}
}

void Gun::render()
{
	// ---- ¡¡¡¡ PASOS PARA RENDERIZAR !!!! ----.

	// reference to the SDLUtils Singleton.
	auto& sdl = *SDLUtils::Instance();

	// store the 'renderer' in a local variable, just for convenience
	SDL_Renderer* renderer = sdl.renderer();

	// fire image.
	auto& fire = sdl.images().at("fire");

	//Recorremos el array de balas
	for (Gun::Bullet& b : _bullets) {
		if (b.used) {

			// Creamos el rectángulo con el tamaño y la posicion inicial.
			SDL_Rect fireRect;
			fireRect.x = b.pos.getX();
			fireRect.y = b.pos.getY();
			
			// por darle un tamaño....
			fireRect.w = b.width;
			fireRect.h = b.height;

			//Renderiza con giro
			fire.render(fireRect, b.rot);
		}
	}
}

void Gun::update()
{
	auto& ihldr = ih();
	int bw = 5;
	int bh = 20;
	Vector2D c = _trPlayer->getPos() + Vector2D(_trPlayer->getWidth() / 2.0f, _trPlayer->getHeight() / 2.0f);
	Vector2D bp = c - Vector2D(bw / 2, _trPlayer->getHeight() / 2.0f + 5.0f + bh).rotate(_trPlayer->getRot()) - Vector2D(bw / 2, bh / 2);
	Vector2D bv = Vector2D(0, -1).rotate(_trPlayer->getRot()) * (_trPlayer->getVel().magnitude() + 5.0f);
	float br = Vector2D(0, -1).angle(bv);

	//Recorremos las balas
	for (Gun::Bullet& b : _bullets) {
		//Si se ha usado
		if (b.used) { 
			//Avanza pos + vel (en línea recta con la rotacion del shoot)
			b.pos.setX(b.pos.getX() + b.vel.getX());
			b.pos.setY(b.pos.getY() + b.vel.getY());

			//Si sale de pantalla, se desactiva
			if (b.pos.getX() + b.getBulletWidth() < 0 || b.pos.getX()> sdlutils().width() ||
				b.pos.getY() + b.getBulletHeight() < 0 || b.pos.getY()> sdlutils().height()) {
				b.used = false;
			}
		}
	}

	// Inicialmente empieza en 0.25 segundos.
	Uint32 _timeBetweenEachSpawn = 250;

	auto& vt = sdlutils().virtualTimer();

	// Puede disparar en caso de apretar la tecla S (meter comprobación de keyDownEvent para evitar que suelte todo el rato).
	if (ihldr.keyDownEvent()) {
		if (ihldr.isKeyDown(SDL_SCANCODE_S) && vt.currTime() > _timeBetweenEachSpawn + _lastShoot){
			//Dispara
			shoot(bp, bv, bw, bh, br);

			// Reinicia el contador
			_lastShoot = vt.currTime();
		}
	}
}

void Gun::shoot(Vector2D p, Vector2D v, int width, int height, float r)
{
	sdlutils().soundEffects().at("fire").play(0, 1);

	//indice para la busqueda circular
	int _lastUsed = 0;
	//i no es 0 hasta que no llegue _lastUsed + 1 no llegue a 20. En otros casos, i = _lastUsed + 1
	int i = (_lastUsed + 1) % _bullets.size();
	//Si la bala está usada (ya se ha disparado), y no es la que acabamos de comprobar
	while (_bullets[i].used && i != _lastUsed) {
		//Avanza la busqueda, porque esa bala ya se ha disparado
		i = (i + 1) % _bullets.size();
	}

	//Si no se ha disparado ya
	if (!_bullets[i].used) {
		//La dispara en la posición y con la velocidad determinada
		_bullets[i].used = true;
		_bullets[i].setBulletPos(p);
		_bullets[i].setBulletVel(v);
		_bullets[i].setBulletRot(r);
		_bullets[i].setBulletWidth(width);
		_bullets[i].setBulletHeight(height);
	}

	
}
