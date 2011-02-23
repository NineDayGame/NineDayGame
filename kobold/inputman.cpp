#include <boost/lexical_cast.hpp>

#include "inputman.hpp"

InputMan::InputMan() {}

void InputMan::set_entity(Entity::ShPtr entity) {
	e_ = entity;
}

void InputMan::set_renderman(RenderMan::ShPtr rman) {
	renderman_ = rman;
}

bool InputMan::read_input() {
	
	bool retVal = false;
	
	while ( SDL_PollEvent( &event_ ) ) {
		if( event_.type == SDL_KEYDOWN ) {
			switch( event_.key.keysym.sym )
			{
				case SDLK_KP1:
				case SDLK_LEFT: e_->move(e_->x-1, e_->y); e_->look(); break;
				case SDLK_KP2: e_->move(e_->x-1, e_->y-1); e_->look(); break;
				case SDLK_KP3:
				case SDLK_DOWN: e_->move(e_->x, e_->y-1); e_->look(); break;
				case SDLK_KP4: e_->move(e_->x-1, e_->y+1); e_->look(); break;
				case SDLK_KP6: e_->move(e_->x+1, e_->y-1); e_->look(); break;
				case SDLK_KP7:
				case SDLK_UP: e_->move(e_->x, e_->y+1); e_->look(); break;
				case SDLK_KP8: e_->move(e_->x+1, e_->y+1); e_->look(); break;
				case SDLK_KP9:
				case SDLK_RIGHT: e_->move(e_->x+1, e_->y); e_->look(); break;
				case SDLK_F1: renderman_->toggle_fullscreen(); break;
				case SDLK_F2: renderman_->toggle_lighting(); break;
				case SDLK_F3: renderman_->toggle_wireframes(); break;
				case SDLK_F12: renderman_->take_screenshot(); break;
			}
		
			renderman_->reload_world();
		}
		
		if ( event_.type == SDL_QUIT ) {
			retVal = true;
		}
	}
	
	return retVal;
}
