#include "main_gamestate.hpp"
#include "menu.hpp"
#include "item.hpp"
#include "util.hpp"
#include "inventory_menu.hpp"
#include "ai.hpp"

GameState::ShPtr GameState::state = GameState::ShPtr();

MainGameState::MainGameState(GameState::ShPtr p, Entity::ShPtr e) : GameState(p), player(e)
{
	
}

void MainGameState::handle_key_press(TCOD_key_t key)
{
	if(key.vk == TCODK_KP8) { player->move(player->x,player->y-1); }
	if(key.vk == TCODK_KP2) { player->move(player->x,player->y+1); }
	if(key.vk == TCODK_KP4) { player->move(player->x-1,player->y); }
	if(key.vk == TCODK_KP6) { player->move(player->x+1,player->y); }
	if(key.vk == TCODK_KP7) { player->move(player->x-1,player->y-1); }
	if(key.vk == TCODK_KP9) { player->move(player->x+1,player->y-1); }
	if(key.vk == TCODK_KP1) { player->move(player->x-1,player->y+1); }
	if(key.vk == TCODK_KP3) { player->move(player->x+1,player->y+1); }
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

	foreach(Container::ShPtr c, player->container.lock()->inventory)
	{
		AI::ShPtr a = DCONVERT(AI,Container,c);
		if(a)
		{
			a->ai();
		}
	}
}

void MainGameState::draw()
{
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
