#include "NewRoundState.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"

void NewRoundState::update()
{
	// --- Text.
	Texture startTex(sdlutils().renderer(), "Press ENTER to start the round",
		sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x444444ff));

	SDL_Rect dest = build_sdlrect( //
		(sdlutils().width() - startTex.width()) / 2.0f, //
		sdlutils().height() - startTex.height() / 2.0f, //
		startTex.width(), //
		startTex.height());

	startTex.render(dest);

	// --- Input.
	InputHandler& ihldr = ih();

	// si el enter es presionado...
	if (ihldr.isKeyDown(SDL_SCANCODE_KP_ENTER)) {
		_fUtils->reset_fighter();
		_aUtils->remove_all_asteroids();
		_aUtils->create_asteroids(10);

		// !!! cambia a RunningState
	}
}
