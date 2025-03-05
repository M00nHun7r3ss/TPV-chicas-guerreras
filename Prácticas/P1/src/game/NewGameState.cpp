#include "NewGameState.h"

#include <algorithm>
#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "../components/Image.h"
#include "../components/Transform.h"

#include "FighterUtils.h"

void NewGameState::update()
{
	// --- Text.
	Texture startTex(sdlutils().renderer(), "Press any key to start a new game",
		sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x444444ff));

	SDL_Rect dest = build_sdlrect( //
		(sdlutils().width() - startTex.width()) / 2.0f, //
		sdlutils().height() - startTex.height() / 2.0f, //
		startTex.width(), //
		startTex.height());

	startTex.render(dest);

	// --- Input.
	InputHandler& ihldr = ih();

	// ya sea por clic o por tecla...
	if (ihldr.mouseButtonDownEvent() || ihldr.keyDownEvent()) {
		_fUtils->reset_lives();
	}
	
	// !!! cambia a NewRoundState
}
