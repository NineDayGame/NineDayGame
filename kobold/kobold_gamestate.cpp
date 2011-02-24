#include "kobold_gamestate.hpp"
#include "util.hpp"
#include "ai.hpp"

KoboldGameState::KoboldGameState(GameState::ShPtr p, RenderMan::ShPtr r, Entity::ShPtr e) : GameState(p), renderer(r), player(e)
{}

void KoboldGameState::handle_input()
{
	SDL_Event event_;
	renderer->reload_world();
	SDL_WaitEvent( &event_ );
	if( event_.type == SDL_KEYDOWN ) {
		switch( event_.key.keysym.sym )
		{
		case SDLK_KP1:
		case SDLK_LEFT: player->move(player->x-1, player->y); break;
		case SDLK_KP2: player->move(player->x-1, player->y-1); break;
		case SDLK_KP3:
		case SDLK_DOWN: player->move(player->x, player->y-1); break;
		case SDLK_KP4: player->move(player->x-1, player->y+1); break;
		case SDLK_KP6: player->move(player->x+1, player->y-1); break;
		case SDLK_KP7:
		case SDLK_UP: player->move(player->x, player->y+1); break;
		case SDLK_KP8: player->move(player->x+1, player->y+1); break;
		case SDLK_KP9:
		case SDLK_RIGHT: player->move(player->x+1, player->y); break;
		case SDLK_F1: renderer->toggle_fullscreen(); break;
		case SDLK_F2: renderer->toggle_lighting(); break;
		case SDLK_F3: renderer->toggle_wireframes(); break;
		case SDLK_F12: renderer->take_screenshot(); break;
		}

		foreach(Container::ShPtr c, player->container.lock()->inventory)
		{
			AI::ShPtr a = DCONVERT(AI,Container,c);
			if(a)
			{
				a->ai();
			}
		}
	}
		
	if ( event_.type == SDL_QUIT ) {
		GameState::running = false;
	}
}
void KoboldGameState::draw()
{
	foreach(Container::ShPtr c, player->container.lock()->inventory)
	{
		Entity::ShPtr e = DCONVERT(Entity,Container,c);
		if(e)
		{
			e->look();
		}
	}
	renderer->draw_frame();
}
