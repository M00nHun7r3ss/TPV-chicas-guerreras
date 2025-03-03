#include "FighterUtils.h"

#include <algorithm>
#include <vector>
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Generations.h"
#include "../components/Follow.h"

#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"
#include "../components/DeAcceleration.h"
#include "../components/FighterCtrl.h"
#include "../components/Health.h"
#include "../components/Gun.h"
#include "../game/AsteroidsUtils.h"

FighterUtils::FighterUtils()
	: _mngr(Game::Instance()->getManager()) {

}

void FighterUtils::create_fighter()
{
	// Create the fighter entity.
	ecs::entity_t fighter = _mngr->addEntity();
	_mngr->setHandler(ecs::hdlr::FIGHTER, fighter);

	Transform* tf = _mngr->addComponent<Transform>(fighter);
	float s = 50.0f;
	float x = (sdlutils().width() - s) / 2.0f;
	float y = (sdlutils().height() - s) / 2.0f;
	tf->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

	_mngr->addComponent<Image>(fighter, &sdlutils().images().at("fighter"));
	_mngr->addComponent<DeAcceleration>(fighter);
	_mngr->addComponent<FighterCtrl>(fighter);
	_mngr->addComponent<ShowAtOppositeSide>(fighter);
	_mngr->addComponent<Health>(fighter);
	_mngr->addComponent<Gun>(fighter, tf);
}
