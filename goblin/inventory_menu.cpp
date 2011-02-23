#include "inventory_menu.hpp"
#include "entity.hpp"
#include "item.hpp"
#include "util.hpp"
#include "main_gamestate.hpp"
#include "whattodo_menu.hpp"

static void create_what_to_do(GameState::ShPtr m, MenuItem* me)
{
	Entity::ShPtr e = SCONVERT(Entity,void,me->args.at(0));
	Item::ShPtr i = SCONVERT(Item,void,me->args.at(1));
	InventoryMenu::ShPtr im = DCONVERT(InventoryMenu,GameState,m);
	WhatToDoMenu::ShPtr wtd(new WhatToDoMenu(im,im->screen_x+im->width,im->screen_y,10,im->height));
	wtd->init(e,i);
	GameState::state = wtd;
}

InventoryMenu::InventoryMenu(GameState::ShPtr parent, int sx, int sy, int w, int h) : Menu(parent,sx,sy,w,h)
{
}
InventoryMenu::~InventoryMenu() {}

void InventoryMenu::init()
{
	MainGameState::ShPtr m = SCONVERT(MainGameState,GameState,get_first_parent());
	Entity::ShPtr e = m->player;
	int i = 1;
	foreach(Container::ShPtr c, e->inventory)
	{
		Item::ShPtr item = SCONVERT(Item,Container,c);
		MenuItem::ShPtr mi(new MenuItem(screen_x+1,screen_y+i,item->name,TCOD_white,&create_what_to_do));
		mi->args.push_back(e);
		mi->args.push_back(item);
		menu_items.push_back(mi);
		++i;
	}
	menu_items.at(selected_index)->select();
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
