#include "menu.hpp"
#include "util.hpp"

Menu::Menu(GameState::ShPtr p, int sx, int sy, int w, int h) : GameState(p), screen_x(sx), screen_y(sy), width(w), height(h), selected_index(0)
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
		mi->draw(console);
	}
}

void Menu::handle_key_press(TCOD_key_t key)
{
	if(key.vk == TCODK_ESCAPE) { GameState::state = parent; }
	if(key.vk == TCODK_SPACE)
	{
		Menu::ShPtr c = Menu::ShPtr(new Menu(this->shared_from_this(),30,10,20,20));
		GameState::state = c;
	}
}
