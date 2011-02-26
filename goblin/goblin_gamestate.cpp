#include "goblin_gamestate.hpp"
#include "menu.hpp"
#include "item.hpp"
#include "util.hpp"
#include "inventory_menu.hpp"
#include "monster.hpp"
#include "living.hpp"
#include "action_scheduler.hpp"
#include <stdio.h>

GoblinGameState::GoblinGameState(GameState::ShPtr p, Living::ShPtr e) : GameState(p), player(e)
{
	
}

void GoblinGameState::handle_input()
{
	Living::ActionArgs args;
	boost::shared_ptr<int> x(new int(player->x));
	boost::shared_ptr<int> y(new int(player->y));
	bool walking = false;
	
	TCODConsole::flush();
	TCOD_key_t key = TCODConsole::waitForKeypress(true);
	//TCOD_key_t key = TCODConsole::checkForKeypress(true);
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
		foreach(Container::ShPtr c, player->inventory)
		{
			Item::ShPtr i = SCONVERT(Item,Container,c); cprintf("%s",i->name.c_str());
		}
	}
	if(key.c == 'i')
	{
		Menu::ShPtr c = InventoryMenu::ShPtr(new InventoryMenu(this->shared_from_this(),5,25,20,20));
		c->init();
		GameState::state = c;
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
}

void GoblinGameState::draw()
{
	char buffer[128];
	Living::ShPtr p = SCONVERT(Living,Entity,player);
	sprintf(buffer,"Health: %d/%d",p->health,p->max_health);
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
