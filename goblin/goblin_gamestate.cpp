#include "goblin_gamestate.hpp"
#include "menu.hpp"
#include "item.hpp"
#include "util.hpp"
#include "inventory_menu.hpp"
#include "action_menu.hpp"
#include "monster.hpp"
#include "living.hpp"
#include "action_scheduler.hpp"
#include "goblin_targetstate.hpp"
#include <stdio.h>

void look_callback(Living::ShPtr e, std::string a, int x, int y)
{
	foreach(Entity::WkPtr c, e->seen)
	{
		Living::ShPtr l = DCONVERT(Living,Entity,c.lock());
		if(l && l->x == x && l->y == y)
		{				
			cprintf("%s    Exp: %d",l->name.c_str(),l->experience);
			cprintf("Health: %d/%d  Mana: %d/%d",l->health,l->max_health,l->mana,l->max_mana);
			cprintf("Str : %02d Mag : %02d",l->str,l->magic);
			cprintf("Dex : %02d Int : %02d",l->dex,l->intel);
			cprintf("Con : %02d Soul: %02d",l->con,l->soul);
			cprintf("Disp: %02d Spd : %.2f",l->disp,l->speed);
			break;
		}
		Item::ShPtr i = DCONVERT(Item,Entity,c.lock());
		if(i && i->x == x && i->y == y)
		{				
			cprintf("%s : %s",i->name.c_str(),i->description.c_str());
			break;
		}
	}
}


GoblinGameState::GoblinGameState(GameState::ShPtr p, Living::ShPtr e) : GameState(p,e)
{
	
}

void GoblinGameState::handle_input()
{
	Living::ActionArgs args;
	boost::shared_ptr<int> x(new int(player->x));
	boost::shared_ptr<int> y(new int(player->y));
	bool walking = false;
	
	TCOD_key_t key;
	if(!player->blocked)
	{
		TCODConsole::flush();
		key = TCODConsole::waitForKeypress(true);
		//key = TCODConsole::checkForKeypress(true);
	}
	if(TCODConsole::isWindowClosed()) { GameState::running = false; return; }
	if(key.vk == TCODK_KP8) { walking = true; --(*y); }
	if(key.vk == TCODK_KP2) { walking = true; ++(*y); }
	if(key.vk == TCODK_KP4) { walking = true; --(*x); }
	if(key.vk == TCODK_KP6) { walking = true; ++(*x); }
	if(key.vk == TCODK_KP7) { walking = true; --(*x); --(*y); }
	if(key.vk == TCODK_KP9) { walking = true; ++(*x); --(*y); }
	if(key.vk == TCODK_KP1) { walking = true; --(*x); ++(*y); } 
	if(key.vk == TCODK_KP3) { walking = true; ++(*x); ++(*y); }
	if(key.vk == TCODK_KP5) { player->wait(args); }
	if(key.vk == TCODK_SPACE) { player->spin_attack(args); }
	if(walking == true)
	{
		args.push_back(x);
		args.push_back(y);
		player->walk(args);
	}
	if(key.c == 'l')
	{
		int x;
		int y;
		int width;
		int height;
		foreach(Camera::ShPtr c, cameras)
		{
			EntityCamera::ShPtr ec = DCONVERT(EntityCamera,Camera,c);
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
		GoblinTargetState::ShPtr gts(new GoblinTargetState(GameState::state,tc,player,"",&look_callback));
		GameState::state = gts;
	}
	if(key.c == 'i')
	{
		Menu::ShPtr c = InventoryMenu::ShPtr(new InventoryMenu(this->shared_from_this(),player,5,25,20,20));
		c->init();
		GameState::state = c;
	}
	if(key.c == 'a')
	{
		Menu::ShPtr c = ActionMenu::ShPtr(new ActionMenu(this->shared_from_this(),player,5,25,20,20));
		c->init();
		GameState::state = c;
	}
	if(key.c == 't')
	{
		int x;
		int y;
		int width;
		int height;
		foreach(Camera::ShPtr c, cameras)
		{
			EntityCamera::ShPtr ec = DCONVERT(EntityCamera,Camera,c);
			if(ec && ec->target == player)
			{
				x = ec->screen_x;
				y = ec->screen_y;
				width = ec->width;
				height = ec->height;
			}
		}
		TargetingCamera::ShPtr tc(new TargetingCamera(player->known_map,player,player->x,player->y,x,y,width,height));
		GameState::state = GoblinTargetState::ShPtr(new GoblinTargetState(this->shared_from_this(),tc,player,"",NULL));
	}

	while(player->blocked)
	{
		foreach(Container::ShPtr c, player->container.lock()->inventory)
		{
			Monster::ShPtr a = DCONVERT(Monster,Container,c);
			if(a && !a->blocked)
			{
				a->ai();
			}
		}
	
		as.tick();
	}

	char c;
	GameState::map->get_data(player->x,player->y,&c,NULL,NULL,NULL);
	if(c == '<')
	{
		GameState::generate_map(GameState::map->width,GameState::map->height);
		GameState::map->get(player);
		player->known_map->clear();
		player->host_map = GameState::map;
		int x,y;
		GameState::map->random_free_spot(&x,&y);
		player->move(x,y);
		cprintf("Welcome to floor %d.",GameState::floor);
	}
}

void GoblinGameState::draw()
{
	GameState::draw();
	char buffer[128];
	sprintf(buffer,"Health: %d/%d  Mana: %d/%d",player->health,player->max_health,player->mana,player->max_mana);
	health_indicator->text.clear();
	health_indicator->print(buffer);
	foreach(Container::ShPtr c, player->container.lock()->inventory)
	{
		Entity::ShPtr e = DCONVERT(Entity,Container,c);
		if(e)
		{
			e->look();
		}
	}
	foreach(Camera::ShPtr c, cameras)
	{
		c->draw();
	}
}
