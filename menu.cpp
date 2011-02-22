#include "main_gamestate.hpp"
#include "menu.hpp"
#include "entity.hpp"
#include "item.hpp"
#include "util.hpp"

#include "menuitem.hpp"

Menu::Menu(GameState::ShPtr p, int sx, int sy, int w, int h) : GameState(p), screen_x(sx), screen_y(sy), width(w), height(h), selected_index(0) {}
Menu::~Menu() {}

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

static void foo(GameState::ShPtr m, MenuItem* me)
{
	cprintf("%s",me->text.c_str());
}

InventoryMenu::InventoryMenu(GameState::ShPtr parent, int sx, int sy, int w, int h) : Menu(parent,sx,sy,w,h)
{
	MainGameState::ShPtr m = SCONVERT(MainGameState,GameState,parent);
	Entity::ShPtr e = m->player;
	int i = 1;
	foreach(Container::ShPtr c, e->inventory)
	{
		Item::ShPtr item = SCONVERT(Item,Container,c);
		MenuItem::ShPtr mi(new MenuItem(screen_x+1,screen_y+i,item->name,TCOD_white,&foo));
		menu_items.push_back(mi);
		++i;
	}
	menu_items.at(selected_index)->select();
}
InventoryMenu::~InventoryMenu() {}
	
void InventoryMenu::draw(TCODConsole* console)
{
	Menu::draw(console);
	foreach(MenuItem::ShPtr mi, menu_items)
	{
		mi->draw(console);
	}
	
}
void InventoryMenu::handle_key_press(TCOD_key_t key)
{
	Menu::handle_key_press(key);
	if(key.vk == TCODK_ENTER)
	{
		foreach(MenuItem::ShPtr mi, menu_items)
		{
			if(mi->selected) { mi->choose(this->shared_from_this()); break; }
		}
	}
	if(key.vk == TCODK_UP)
	{
		menu_items.at(selected_index)->unselect();
		selected_index = (selected_index-1)%menu_items.size();
		menu_items.at(selected_index)->select();
	}
	if(key.vk == TCODK_DOWN)
	{
		menu_items.at(selected_index)->unselect();
		selected_index = (selected_index+1)%menu_items.size();
		menu_items.at(selected_index)->select();
	}
}
