#include "gamestate.hpp"
#include "item.hpp"
#include "monster.hpp"
#include <libtcod.hpp>
#include <stdio.h>

GameState::ShPtr GameState::state = GameState::ShPtr();
Map::ShPtr GameState::map = Map::ShPtr();

bool GameState::running = true;

void GameState::generate_map(int width, int height)
{
	map = Map::ShPtr(new Map(width,height));
	map->clear();
	map->randomize(40);

	TCODRandom* rand = TCODRandom::getInstance();
	for(int i = 0; i < 50; ++i)
	{
		char buf[32];
		char name[32];
		char desc[128];
		int x,y;
		map->random_free_spot(&x,&y);
		sprintf(buf,"Entity %d",i);
		sprintf(name,"health potion");
		sprintf(desc,"a potion that restores up to 10 health");

		TCODColor color(rand->getInt(0,255),rand->getInt(0,255),rand->getInt(0,255));
		Monster::ShPtr e(new Monster(Map::WkPtr(map),buf,x,y,1,color,3));
		e->init_stats(8,3,5,5,6,3,3,1);
		Item::ShPtr i(new Item(Map::WkPtr(map),name,desc,x,y,'I',TCOD_green));
		e->get(i);
		map->get(e);
	}
}
