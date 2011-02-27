#include "KoboldItemActionMenu.hpp"
#include "util.hpp"
#include "living.hpp"

static void look(GameState::ShPtr m, MenuItem* me)
{
	Entity::ShPtr e = SCONVERT(Entity,void,me->args.at(0));
	Item::ShPtr i = SCONVERT(Item,void,me->args.at(1));
	KoboldItemActionMenu::ShPtr am = SCONVERT(KoboldItemActionMenu, void, m);
	am->renderman_->remove_window(am->menu_window_);
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
	KoboldItemActionMenu::ShPtr am = SCONVERT(KoboldItemActionMenu, void, m);
	am->renderman_->remove_window(am->menu_window_);
	KoboldInventoryMenu::ShPtr im = SCONVERT(KoboldInventoryMenu, void, am->parent);
	im->renderman_->remove_window(im->menu_window_);
	cprintf("%s dropped the %s",e->name.c_str(),i->name.c_str());
	GameState::state = m->parent->parent;
}

static void use(GameState::ShPtr m, MenuItem* me)
{
	Living::ShPtr e = SCONVERT(Living,void,me->args.at(0));
	Item::ShPtr i = SCONVERT(Item,void,me->args.at(1));
	i->use(e);
	e->remove(i);
	KoboldItemActionMenu::ShPtr am = SCONVERT(KoboldItemActionMenu, void, m);
	am->renderman_->remove_window(am->menu_window_);
	KoboldInventoryMenu::ShPtr im = SCONVERT(KoboldInventoryMenu, void, am->parent);
	im->renderman_->remove_window(im->menu_window_);
	GameState::state = m->parent->parent;
}

KoboldItemActionMenu::KoboldItemActionMenu(GameState::ShPtr parent, Living::ShPtr player, int sx, int sy, int w, int h) : KoboldInventoryMenu(parent,player,sx,sy,w,h)
{
	
}

KoboldItemActionMenu::~KoboldItemActionMenu() {}

void KoboldItemActionMenu::init(Entity::ShPtr e, Item::ShPtr i)
{
	MenuItem::ShPtr mi;
	std::string s;
	int j = 1;
	
	menu_window_.reset(new MenuWindow());
	menu_window_->set_position(screen_x, screen_y, 0);
	menu_window_->set_scale(width, height, 0);
	menu_window_->show();
	
	menu_items.clear();
	
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
