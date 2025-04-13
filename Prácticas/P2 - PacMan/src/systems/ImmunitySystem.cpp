#include "ImmunitySystem.h"

#include "../components/Transform.h"
#include "../ecs/Manager.h"
#include "../components/MiraculousComponent.h"
#include "../utils/Collisions.h"

#include <vector>

ImmunitySystem::ImmunitySystem()
	: _isImmune(false),
	  _lastImmunityStarted(0)
{
	// TODO Auto-generated constructor stub
}

ImmunitySystem::~ImmunitySystem(){
	// TODO Auto-generated destructor stub
}

void ImmunitySystem::initSystem(){
}

void ImmunitySystem::update()
{
	VirtualTimer& vt = sdlutils().virtualTimer();
	Uint32 _timeInImmunity;
	Message mes;

	// si esta en inmunidad...
	if (_isImmune)
	{
		_timeInImmunity = 10000; // 10S

		//Pasado ese tiempo
		if (vt.currRealTime() > _timeInImmunity + _lastImmunityStarted) {
			
			_isImmune = false; // pasados los 10s apaga la inmunidad.
			mes.id = _m_IMMUNITY_END;
			Game::Instance()->getManager()->send(mes);

		}
	}
	//No es que se haya acabado la inmunidad, sino que esta desactivada,
	//para tenerlo de serie y poder comprobar las colisiones con los fantasmas
	else
	{
		mes.id = _m_IMMUNITY_END;
		Game::Instance()->getManager()->send(mes);
	}

}

void ImmunitySystem::recieve(const Message& m)
{
	// mensajes a enviar.
	Message mes;
	VirtualTimer& vt = sdlutils().virtualTimer();

	//Si colisiona con una fruta
	if (m.id == _m_PACMAN_FOOD_COLLISION)
	{
		// en caso de que la entidad fruta sea milagrosa.
		ecs::entity_t e = m.pacman_food_collision_data.f;
		//Comprueba si la fruta puede ser milagrosa
		if (_mngr->hasComponent<MiraculousComponent>(e))
		{
			MiraculousComponent* mc = _mngr->getComponent<MiraculousComponent>(e);

			// si pacman colisiona con una fruta milagrosa...
			if (mc->_isMiraculous) {
				// envia mensaje de que ha comenzado la inmunidad.
				mes.id = _m_IMMUNITY_START;
				Game::Instance()->getManager()->send(mes);
				_isImmune = true;

				//Reseteamos el tiempo actual al coger la fruta para evitar que se modifique todo el rato
				_lastImmunityStarted = vt.currRealTime();
			}
		}
	}

	
	

}
