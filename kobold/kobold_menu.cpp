#include <iostream>
#include "kobold_menu.hpp"
#include "util.hpp"

KoboldMenu::KoboldMenu(GameState::ShPtr p, Living::ShPtr player, int sx, int sy, int w, int h) 
	: Menu(p, player, sx, sy, w, h),
    selected_(0)//, menu_offset(0)
{
	init();
}

KoboldMenu::~KoboldMenu() {}

void KoboldMenu::init() {}

void KoboldMenu::draw()
{
	parent->draw();
}

void KoboldMenu::handle_input()
{
	SDL_Event event_;
	
	SDL_WaitEvent( &event_ );
	if( event_.type == SDL_KEYDOWN ) {
		switch( event_.key.keysym.sym )
		{
		case SDLK_ESCAPE: 
			renderman_->remove_window(menu_window_);
			GameState::state = parent;
			break;
		case SDLK_RETURN:
		case SDLK_KP_ENTER:
			std::cout << "Selected " << menu_items.at(menu_window_->get_selected_index())->text << std::endl;
			menu_items.at(menu_window_->get_selected_index())->choose(this->shared_from_this()); break;
			/*foreach(MenuItem::ShPtr mi, menu_items)
			{
				if(mi->selected) { mi->choose(this->shared_from_this()); break; }
			}*/
			break;
		case SDLK_DOWN:
		case SDLK_KP2:
			menu_items.at(menu_window_->get_selected_index())->unselect();
			menu_window_->select_next();
			menu_items.at(menu_window_->get_selected_index())->select();
			break;
		case SDLK_UP:
		case SDLK_KP8:
			menu_items.at(menu_window_->get_selected_index())->unselect();
			menu_window_->select_prev();
			menu_items.at(menu_window_->get_selected_index())->select();
			break;
		}
	}
	
	if ( event_.type == SDL_QUIT ) {
		GameState::running = false;
	}
}

void KoboldMenu::set_font(Font::ShPtr font) {
	font_ = font;
	menu_window_->set_font(font_);
}

void KoboldMenu::set_renderman(RenderMan::ShPtr renderman) {
	renderman_ = renderman;
	renderman_->add_window(menu_window_);
}
	
	/*TCODConsole::flush();
	TCOD_key_t key = TCODConsole::waitForKeypress(true);

	if(TCODConsole::isWindowClosed()) { GameState::running = false; return; }
	if(key.vk == TCODK_ESCAPE) { GameState::state = parent; }
	if(key.vk == TCODK_ENTER || key.vk == TCODK_KPENTER)
	{
		foreach(MenuItem::ShPtr mi, menu_items)
		{
			if(mi->selected) { mi->choose(this->shared_from_this()); break; }
		}
	}
	if(key.vk == TCODK_UP || key.vk == TCODK_KP8)
	{
		menu_items.at(selected_index)->unselect();
		if(selected_index > 0)
		{
			selected_index = (selected_index-1)%menu_items.size();
			if(menu_items.at(selected_index)->y-menu_offset < screen_y+height-2 && menu_offset > 0)
			{
				--menu_offset;
			}
		}
		menu_items.at(selected_index)->select();
	}
	if(key.vk == TCODK_DOWN || key.vk == TCODK_KP2)
	{
		menu_items.at(selected_index)->unselect();
		if(selected_index < menu_items.size()-1)
		{
			selected_index = (selected_index+1);
			if(menu_items.at(selected_index)->y > screen_y+height-2)
			{
				++menu_offset;
			}
		}
		menu_items.at(selected_index)->select();
	}
}*/
