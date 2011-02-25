#include "kobold_gamestate.hpp"
#include "util.hpp"
#include "monster.hpp"
#include "action_scheduler.hpp"

KoboldGameState::KoboldGameState(GameState::ShPtr p, RenderMan::ShPtr r, Living::ShPtr e) : GameState(p), renderer(r), player(e)
{}

void KoboldGameState::handle_input()
{
	SDL_Event event_;

	Living::ActionArgs args;
	boost::shared_ptr<int> x(new int(player->x));
	boost::shared_ptr<int> y(new int(player->y));
	bool walking = false;
	
	renderer->reload_world();
	SDL_WaitEvent( &event_ );
	if( event_.type == SDL_KEYDOWN ) {
		switch( event_.key.keysym.sym )
		{
		case SDLK_KP1:
		case SDLK_LEFT: walking = true; --(*x); break; 
		case SDLK_KP2: walking = true; --(*x); --(*y); break; 
		case SDLK_KP3:
		case SDLK_DOWN: walking = true; --(*y); break;
		case SDLK_KP4: walking = true; --(*x); ++(*y); break;
		case SDLK_KP5: player->wait(args); break;
		case SDLK_KP6: walking = true; ++(*x); --(*y); break; 
		case SDLK_KP7:
		case SDLK_UP: walking = true; ++(*y); break; 
		case SDLK_KP8: walking = true; ++(*x); ++(*y); break; 
		case SDLK_KP9:
		case SDLK_RIGHT: walking = true; ++(*x); break;
		case SDLK_F1: renderer->toggle_fullscreen(); break;
		case SDLK_F2: renderer->toggle_lighting(); break;
		case SDLK_F3: renderer->toggle_wireframes(); break;
		case SDLK_F12: renderer->take_screenshot(); break;
		case SDLK_SPACE: player->spin_attack(args); break;
		}

		if(walking == true)
		{			
			args.push_back(x);
			args.push_back(y);
			player->walk(args);
		}
	}
		
	if ( event_.type == SDL_QUIT ) {
		GameState::running = false;
	}

	while(player->blocked)
	{
		foreach(Container::ShPtr c, player->container.lock()->inventory)
		{
			Monster::ShPtr a = DCONVERT(Monster,Container,c);
			if(a && !a->blocked)
			{
				a->ai();
			}
		}

		as.tick();
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
