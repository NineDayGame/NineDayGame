#include "menu.hpp"
#include "util.hpp"

Menu::Menu(GameState::ShPtr p, int sx, int sy, int w, int h) : GameState(p), screen_x(sx), screen_y(sy), width(w), height(h), selected_index(0), menu_offset(0)
{
}
Menu::~Menu() {}

void Menu::init() {}

void Menu::draw(TCODConsole* console)
{
	GameState::draw(console);
	console->rect(screen_x,screen_y,width,height,true);
	for(int x = screen_x; x < screen_x+width; ++x)
	{
		console->setChar(x,screen_y,'#');
		console->setFore(x,screen_y,TCOD_white);
		console->setChar(x,screen_y+height-1,'#');
		console->setFore(x,screen_y+height-1,TCOD_white);
	}
	for(int y = screen_y; y < screen_y+height; ++y)
	{
		console->setChar(screen_x,y,'#');
		console->setFore(screen_x,y,TCOD_white);
		console->setChar(screen_x+width-1,y,'#');
		console->setFore(screen_x+width-1,y,TCOD_white);
	}
	foreach(MenuItem::ShPtr mi, menu_items)
	{
		mi->y -= menu_offset;
		if(mi->y > screen_y && mi->y < screen_y+height-1)
		{
			mi->draw(console);
		}
		mi->y += menu_offset;
	}
}

void Menu::handle_key_press(TCOD_key_t key)
{
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
}
