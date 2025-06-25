#include "ShieldSystem.h"

#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"

ShieldSystem::ShieldSystem()
	: _isShieldOn(false),
	_lastShieldStarted(0),
	_N(), _M(), _X(), _T() {
}

ShieldSystem::~ShieldSystem() {
}

void ShieldSystem::initSystem() {
}

void ShieldSystem::update()
{
	VirtualTimer& vt = sdlutils().virtualTimer();
	Message mes;

	// si esta en escudo...
	if (_isShieldOn)
	{
		_T = 5000; // 5S

		//Pasado ese tiempo
		if (vt.currRealTime() > _T + _lastShieldStarted) {

			_isShieldOn = false; // pasados los 5s apaga el escudo
			mes.id = _m_SHIELD_END;
			Game::Instance()->getManager()->send(mes);
		}
	}
	//No es que se haya acabado el escudo, sino que esta desactivada,
	//para tenerlo de serie y poder comprobar las colisiones con los fantasmas
	else
	{
		mes.id = _m_IMMUNITY_END;
		Game::Instance()->getManager()->send(mes);
	}

}

void ShieldSystem::recieve(const Message& m)
{
	//// en caso de que la entidad fruta sea milagrosa.
	//ecs::entity_t e = m.pacman_food_collision_data.f;
	//switch (m.id) {
	//case _m_PACMAN_FOOD_COLLISION:
	//	//Comprueba si la fruta puede ser milagrosa
	//	if (_mngr->hasComponent<MiraculousComponent>(e))
	//	{
	//		MiraculousComponent* mc = _mngr->getComponent<MiraculousComponent>(e);

	//		// si pacman colisiona con una fruta milagrosa...
	//		if (mc->_isMiraculous) {
	//			// mensajes a enviar.
	//			Message mes;
	//			VirtualTimer& vt = sdlutils().virtualTimer();
	//			// envia mensaje de que ha comenzado la inmunidad.
	//			mes.id = _m_IMMUNITY_START;
	//			Game::Instance()->getManager()->send(mes);
	//			_isImmune = true;

	//			//Reseteamos el tiempo actual al coger la fruta para evitar que se modifique todo el rato
	//			_lastImmunityStarted = vt.currRealTime();
	//		}
	//	}
	//	break;
	//default:
	//	break;
	//}

}
