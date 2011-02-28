#include "kobold_deadstate.hpp"
#include "SDL/SDL.h"

KoboldDeadState::KoboldDeadState(GameState::ShPtr parent, Living::ShPtr player) : GameState(parent,player) {}
KoboldDeadState::~KoboldDeadState() {}

void KoboldDeadState::handle_input()
{
	SDL_Event event_;
	SDL_WaitEvent(&event_);
	if(event_.type == SDL_KEYDOWN && event_.key.keysym.sym == SDLK_ESCAPE)
	{
		GameState::running = false;
		GameState::state = parent;
	}
}
