#include <boost/lexical_cast.hpp>
#include "gamestate.hpp"
#include "item.hpp"
#include "monster.hpp"
#include <libtcod.hpp>

GameState::ShPtr GameState::state = GameState::ShPtr();
Map::ShPtr GameState::map = Map::ShPtr();
int GameState::floor = 0;

bool GameState::running = true;

void GameState::generate_map(int width, int height)
{
	++GameState::floor;
	map = Map::ShPtr(new Map(width,height));
	map->clear();
	map->randomize(40);

	TCODRandom* rand = TCODRandom::getInstance();
	std::string item_name = "Health Potion";
	std::string item_desc = "A potion that restores up to 10 health.";
	for(int i = 0; i < 50; ++i)
	{
		std::string entity_name = "Zom";
		switch(i%5)
		{
		case 0: entity_name += "borg"; break;
		case 1: entity_name += "gord"; break;
		case 2: entity_name += "beast"; break;
		case 3: entity_name += "berl"; break;
		case 4: entity_name += "flord"; break;
		}
		entity_name += boost::lexical_cast<std::string>(i);
		
		int x,y;
		map->random_free_spot(&x,&y);

		TCODColor color(rand->getInt(0,255),rand->getInt(0,255),rand->getInt(0,255));
		Monster::ShPtr e(new Monster(Map::WkPtr(map),entity_name,x,y,1,color,3));
		e->init_stats(8+rand->getInt(0,GameState::floor),
		              3+rand->getInt(0,GameState::floor),
		              5+rand->getInt(0,GameState::floor),
		              5+rand->getInt(0,GameState::floor),
		              6+rand->getInt(0,GameState::floor),
		              3+rand->getInt(0,GameState::floor),
		              3+rand->getInt(0,GameState::floor),
		              1);
		if(rand->getFloat(0.0,1.0) > 0.85f)
		{
			TCODColor color_item(rand->getInt(0,255),rand->getInt(0,255),rand->getInt(0,255));
			Item::ShPtr i(new Item(Map::WkPtr(map),item_name,item_desc,x,y,'I',color_item));
			e->get(i);
		}
		map->get(e);
	}
}

Living::ShPtr GameState::generate_player()
{
	int x,y;
	GameState::map->random_free_spot(&x,&y);
	Living::ShPtr e(new Living(Map::WkPtr(GameState::map),"Hero",x,y,'@',TCOD_red,30000));
	e->init_stats(12,8,8,8,15,8,8,1);
	GameState::map->get(e);
	return e;
}
