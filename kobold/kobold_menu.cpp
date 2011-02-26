#include "kobold_menu.hpp"
#include "util.hpp"

KoboldMenu::KoboldMenu(GameState::ShPtr p, int sx, int sy, int w, int h) 
  : Menu(p, sx, sy, w, h)//, selected_index(0), menu_offset(0)
{
	init();
}

KoboldMenu::~KoboldMenu() {}

void KoboldMenu::init() {
	//const Font::ShPtr cfont = p->fontman_->get_font("resources/terminal.bmp");
	
	menu_window_.reset(new MenuWindow());
	//menu_window_->set_font(cfont);
	menu_window_->set_position(400, 200, 0);
	menu_window_->set_scale(200, 200, 0);
	menu_window_->show();
	menu_window_->push_item(std::string("Menu item 1"));
	menu_window_->push_item(std::string("Menu item 2"));
	menu_window_->push_item(std::string("Menu item 3"));
	//parent->renderer->add_window(menu_window_);
}

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
		}
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
