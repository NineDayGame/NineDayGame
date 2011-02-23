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
	WhatToDoMenu::ShPtr wtd(new WhatToDoMenu(im,im->screen_x+im->width,im->screen_y,10,4));
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
	if(menu_items.size() > 0)
	{
		menu_items.at(selected_index)->select();
	}
}
