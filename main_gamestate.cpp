#include "main_gamestate.hpp"
#include "menu.hpp"
#include "item.hpp"
#include "util.hpp"

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
	if(key.c == 'm')
	{
		Menu::ShPtr c = Menu::ShPtr(new Menu(this->shared_from_this(),10,10,20,20));
		GameState::state = c;
	}
}

void MainGameState::draw(TCODConsole* console)
{
	foreach(Camera::ShPtr c, cameras)
	{
		c->draw(console);
	}
}
