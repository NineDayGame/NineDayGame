#include <cmath>
#include "action_menu.hpp"
#include "living.hpp"
#include "item.hpp"
#include "util.hpp"
#include "goblin_gamestate.hpp"
#include "goblin_targetstate.hpp"

void target_callback(Living::ShPtr e, std::string a, int x, int y)
{
	Living::ActionInfo i = e->actions_info[a];
	boost::shared_ptr<int> sx(new int(x));
	boost::shared_ptr<int> sy(new int(y));
	Living::ActionArgs args;
	
	switch(i.get<ACTION_TARGET>())
	{
	case Living::TARGET_NONE:
		break;
	case Living::TARGET_LIVING:
		foreach(Entity::WkPtr c, e->seen)
		{
			Living::ShPtr l = DCONVERT(Living,Entity,c.lock());
			if(l && l->x == x && l->y == y)
			{				
				args.push_back(l);
				break;
			}
		}
		break;
	case Living::TARGET_ITEM:
		foreach(Entity::WkPtr c, e->seen)
		{
			Item::ShPtr l = DCONVERT(Item,Entity,c.lock());
			if(l && l->x == x && l->y == y)
			{				
				args.push_back(l);
				break;
			}
		}
		break;
	case Living::TARGET_PLACE:		
		args.push_back(sx);
		args.push_back(sy);
		break;
	case Living::TARGET_DIRECTION:
		if(y == e->y && x == e->x) break;
		
		boost::shared_ptr<double> angle(new double(atan2(y-e->y,x-e->x)));
		args.push_back(angle);
		break;
	}

	((*e).*(e->actions[a]))(args);
}

void target_action(GameState::ShPtr m, MenuItem* me)
{
	Living::ShPtr player = SCONVERT(Living,void,me->args[0]);
	boost::shared_ptr<std::string> action = SCONVERT(std::string,void,me->args[1]);

	if(player->actions_info[*action].get<ACTION_TARGET>() == Living::TARGET_NONE)
	{
		Living::ActionArgs args;
		((*player).*(player->actions[*action]))(args);
		GameState::state = m->parent;
		return;
	}
	
	GoblinGameState::ShPtr gs = SCONVERT(GoblinGameState,GameState,m->get_first_parent());

	int x;
	int y;
	int width;
	int height;
	foreach(Camera::ShPtr c, gs->cameras)
	{
		EntityCamera::ShPtr ec = DCONVERT(EntityCamera,Camera,gs->cameras.front());
		if(ec && ec->target == player)
		{
			x = ec->screen_x;
			y = ec->screen_y;
			width = ec->width;
			height = ec->height;
			break;
		}
	}

	TargetingCamera::ShPtr tc(new TargetingCamera(player->known_map,player,player->x,player->y,x,y,width,height));
	GoblinTargetState::ShPtr gts(new GoblinTargetState(m,tc,player,*(action.get()),&target_callback));
	GameState::state = gts;
}

ActionMenu::ActionMenu(GameState::ShPtr parent, Living::ShPtr player, int sx, int sy, int w, int h) : GoblinMenu(parent,player,sx,sy,w,h)
{
}
ActionMenu::~ActionMenu() {}

void ActionMenu::init()
{
	int i = 1;
	foreach(Living::ActionMap::value_type v, player->actions)
	{
		if(player->GET_ACTION_INFO(v.first,ACTION_MANA) > 0)
		{
			std::string s = player->actions_info[v.first].get<ACTION_NAME>();
			MenuItem::ShPtr mi(new MenuItem(screen_x+1,screen_y+i,s,TCOD_white,&target_action));
			mi->args.push_back(player);
			mi->args.push_back(boost::shared_ptr<std::string>(new std::string(v.first)));
			menu_items.push_back(mi);
			++i;
		}
	}
	if(menu_items.size() > 0)
	{
		menu_items.at(selected_index)->select();
	}
}
