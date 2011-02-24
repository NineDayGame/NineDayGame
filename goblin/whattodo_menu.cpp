#include "whattodo_menu.hpp"
#include "util.hpp"
#include "living.hpp"

static void look(GameState::ShPtr m, MenuItem* me)
{
	Entity::ShPtr e = SCONVERT(Entity,void,me->args.at(0));
	Item::ShPtr i = SCONVERT(Item,void,me->args.at(1));
	cprintf("%s: %s",i->name.c_str(),i->description.c_str());
	GameState::state = m->parent;
}

static void drop(GameState::ShPtr m, MenuItem* me)
{
	Living::ShPtr e = SCONVERT(Living,void,me->args.at(0));
	Item::ShPtr i = SCONVERT(Item,void,me->args.at(1));
	i->x = e->x;
	i->y = e->y;
	e->remove(i);
	e->host_map.lock()->get(i);
	cprintf("%s dropped the %s",e->name.c_str(),i->name.c_str());
	GameState::state = m->parent->parent;
}

WhatToDoMenu::WhatToDoMenu(GameState::ShPtr parent, int sx, int sy, int w, int h) : InventoryMenu(parent,sx,sy,w,h)
{
	
}

WhatToDoMenu::~WhatToDoMenu() {}

void WhatToDoMenu::init(Entity::ShPtr e, Item::ShPtr i)
{
	MenuItem::ShPtr mi;
	std::string s;
	int j = 1;
	
	s = "Look";
	mi = MenuItem::ShPtr(new MenuItem(screen_x+1,screen_y+j++,s,TCOD_white,&look));
	mi->args.push_back(e);
	mi->args.push_back(i);
	menu_items.push_back(mi);

	s = "Drop";
	mi = MenuItem::ShPtr(new MenuItem(screen_x+1,screen_y+j++,s,TCOD_white,&drop));
	mi->args.push_back(e);
	mi->args.push_back(i);
	menu_items.push_back(mi);

	menu_items.at(selected_index)->select();
}
