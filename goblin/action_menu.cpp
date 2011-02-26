#include "action_menu.hpp"
#include "living.hpp"
#include "util.hpp"
#include "goblin_gamestate.hpp"

void foo(GameState::ShPtr m, MenuItem* me)
{
	cprintf("foo");
}

ActionMenu::ActionMenu(GameState::ShPtr parent, int sx, int sy, int w, int h) : GoblinMenu(parent,sx,sy,w,h)
{
}
ActionMenu::~ActionMenu() {}

void ActionMenu::init()
{
	GoblinGameState::ShPtr m = SCONVERT(GoblinGameState,GameState,get_first_parent());
	Entity::ShPtr e = m->player;
	int i = 1;
	foreach(Living::ActionMap::value_type v, m->player->actions)
	{
		std::string s = v.first;
		MenuItem::ShPtr mi(new MenuItem(screen_x+1,screen_y+i,s,TCOD_white,&foo));
		// mi->args.push_back(e);
		// mi->args.push_back(item);
		menu_items.push_back(mi);
		++i;
	}
	if(menu_items.size() > 0)
	{
		menu_items.at(selected_index)->select();
	}
}
