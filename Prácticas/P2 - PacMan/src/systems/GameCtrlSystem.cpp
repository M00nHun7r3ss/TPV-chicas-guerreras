//// This file is part of the course TPV2@UCM - Samir Genaim
//
//#include "GameCtrlSystem.h"
//
//#include "../components/Points.h"
//#include "../ecs/Manager.h"
//#include "../sdlutils/InputHandler.h"
//#include "GhostSystem.h"
//GameCtrlSystem::GameCtrlSystem() :
//		_score() {
//	// TODO Auto-generated constructor stub
//
//}
//
//GameCtrlSystem::~GameCtrlSystem() {
//	// TODO Auto-generated destructor stub
//}
//
//void GameCtrlSystem::initSystem() {
//}
//
//void GameCtrlSystem::update() {
//	auto &ihldr = ih();
//
//	if (ihldr.keyDownEvent()) {
//		if (ihldr.isKeyDown(SDL_SCANCODE_SPACE)) {
//
//			Message m;
//			m.id = _m_CREATE_GHOST;
//			m.create_ghost_data.n = 5;
//			_mngr->send(m);
//		}
//	}
//}
//
//void GameCtrlSystem::recieve(const Message &m) {
//	switch (m.id) {
//	case _m_GHOST_EATEN:
//		_score += _mngr->getComponent<Points>(m.ghost_eaten_data.e)->_points;
//		break;
//	default:
//		break;
//	}
//}
