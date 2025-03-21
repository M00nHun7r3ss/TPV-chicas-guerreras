#include "FighterUtils.h"

#include "../ecs/Manager.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

#include "../utils/Vector2D.h"

#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/DeAcceleration.h"
#include "../components/FighterCtrl.h"
#include "../components/Health.h"
#include "../components/Gun.h"


FighterUtils::FighterUtils()
	: _mngr(Game::Instance()->getManager()), _fighter() {

}

void FighterUtils::create_fighter()
{
	// Create the fighter entity.
	_fighter = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::FIGHTER, _fighter);

	//Lo coloca en el centro de la pantalla con todas sus cositas
	Transform* tf = _mngr->addComponent<Transform>(_fighter);
	reset_fighter_pos();

	//Anade componentes
	_mngr->addComponent<Image>(_fighter, &sdlutils().images().at("fighter"));
	_mngr->addComponent<DeAcceleration>(_fighter);
	_mngr->addComponent<FighterCtrl>(_fighter);
	_mngr->addComponent<ShowAtOppositeSide>(_fighter);
	_mngr->addComponent<Health>(_fighter);
	_mngr->addComponent<Gun>(_fighter, tf);

	//Resetea la vida a 3
	reset_lives();
}

void FighterUtils::reset_fighter()
{
	//Resetea la posici�n
	reset_fighter_pos();

	//Resetea Gun
	_mngr->getComponent<Gun>(_mngr->getHandler(ecs::hdlr::FIGHTER))->reset();
}

void FighterUtils::reset_lives()
{
	_mngr->getComponent<Health>(_mngr->getHandler(ecs::hdlr::FIGHTER))->heal();
}

int FighterUtils::update_lives(int n)
{
	//Quita n vidas
	_mngr->getComponent<Health>(_mngr->getHandler(ecs::hdlr::FIGHTER))->damage(n);

	//Devuelve la vida actual
	return _mngr->getComponent<Health>(_mngr->getHandler(ecs::hdlr::FIGHTER))->getHealth();
}

void FighterUtils::reset_fighter_pos()
{
	//Resetea la posici�n
	float s = 50.0f;
	float x = (sdlutils().width() - s) / 2.0f;
	float y = (sdlutils().height() - s) / 2.0f;
	_mngr->getComponent<Transform>(_mngr->getHandler(ecs::hdlr::FIGHTER))->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);
}
