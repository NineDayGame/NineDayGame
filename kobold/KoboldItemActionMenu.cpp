#include "KoboldItemActionMenu.hpp"
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

static void use(GameState::ShPtr m, MenuItem* me)
{
	Living::ShPtr e = SCONVERT(Living,void,me->args.at(0));
	Item::ShPtr i = SCONVERT(Item,void,me->args.at(1));
	i->use(e);
	e->remove(i);
	GameState::state = m->parent->parent;
}

KoboldItemActionMenu::KoboldItemActionMenu(GameState::ShPtr parent, int sx, int sy, int w, int h) : KoboldInventoryMenu(parent,sx,sy,w,h)
{
	
}

KoboldItemActionMenu::~KoboldItemActionMenu() {}

void KoboldItemActionMenu::init(Entity::ShPtr e, Item::ShPtr i)
{
	MenuItem::ShPtr mi;
	std::string s;
	int j = 1;
	
	menu_window_.reset(new MenuWindow());
	menu_window_->set_position(200, 200, 0);
	menu_window_->set_scale(40, 40, 0);
	menu_window_->show();
	
	s = "Look";
	mi = MenuItem::ShPtr(new MenuItem(screen_x+1,screen_y+j++,s,TCOD_white,&look));
	mi->args.push_back(e);
	mi->args.push_back(i);
	menu_items.push_back(mi);
	menu_window_->push_item(mi->text);

	s = "Use";
	mi = MenuItem::ShPtr(new MenuItem(screen_x+1,screen_y+j++,s,TCOD_white,&use));
	mi->args.push_back(e);
	mi->args.push_back(i);
	menu_items.push_back(mi);
	menu_window_->push_item(mi->text);

	s = "Drop";
	mi = MenuItem::ShPtr(new MenuItem(screen_x+1,screen_y+j++,s,TCOD_white,&drop));
	mi->args.push_back(e);
	mi->args.push_back(i);
	menu_items.push_back(mi);
	menu_window_->push_item(mi->text);

	menu_items.at(selected_index)->select();
}
