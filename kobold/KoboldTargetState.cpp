#include <iostream>
#include "KoboldTargetState.hpp"
#include "util.hpp"

#include "targeter.hpp"

KoboldTargetState::KoboldTargetState(GameState::ShPtr p, Living::ShPtr player, GlCamera::ShPtr camera, RenderMan::ShPtr renderman, GoblinTargetState::TargetCallback callback, int x, int y) 
	: GameState(p,player),
    camera_(camera),
    renderman_(renderman),
    callback_(callback),
    x_(x), y_(y)
{
	init();
}

void KoboldTargetState::init() {
	reticule_.reset(new Targeter());
	reticule_->set_position(x_, y_-0.5f, 0.501f);
	//TCODColor c = m->color;
	//chr->set_texture(defaultid);
	//reticule_->set_color(Vector3f((c.r/255.0f), (c.g/255.0f), (c.b/255.0f)));
	//reticule_->set_color(Vector3f((c.r/255.0f), (c.g/255.0f), (c.b/255.0f)));
	renderman_->add_movable(reticule_);
}

KoboldTargetState::~KoboldTargetState() {}

void KoboldTargetState::draw()
{
	parent->draw();
}

void KoboldTargetState::handle_input()
{
	SDL_Event event_;
	
	SDL_WaitEvent( &event_ );
	if( event_.type == SDL_KEYDOWN ) {
		switch( event_.key.keysym.sym )
		{
		case SDLK_ESCAPE:
			GameState::state = parent;
			break;
		case SDLK_RETURN:
		case SDLK_KP_ENTER: {
			if(callback_)
			{			
				(*callback_)(player, std::string("hi"), x_, y_);
			}
			break; }
		case SDLK_KP1: camera_->set_coords(--x_, y_); reticule_->set_position(x_, y_-0.5f, 0.501f); break;
		case SDLK_DOWN:
		case SDLK_KP2: camera_->set_coords(--x_, --y_);	reticule_->set_position(x_, y_-0.5f, 0.501f); break;
		case SDLK_KP3: camera_->set_coords(x_, --y_); reticule_->set_position(x_, y_-0.5f, 0.501f); break;
		case SDLK_LEFT:
		case SDLK_KP4: camera_->set_coords(--x_, ++y_); reticule_->set_position(x_, y_-0.5f, 0.501f); break;
		case SDLK_RIGHT:
		case SDLK_KP6: camera_->set_coords(++x_, --y_); reticule_->set_position(x_, y_-0.5f, 0.501f); break; 
		case SDLK_KP7: camera_->set_coords(x_, ++y_); reticule_->set_position(x_, y_-0.5f, 0.501f); break;
		case SDLK_UP:
		case SDLK_KP8: camera_->set_coords(++x_, ++y_);	reticule_->set_position(x_, y_-0.5f, 0.501f); break;
		case SDLK_KP9: camera_->set_coords(++x_, y_); reticule_->set_position(x_, y_-0.5f, 0.501f); break;
		}
	}
	
	if ( event_.type == SDL_QUIT ) {
		GameState::running = false;
	}
}
