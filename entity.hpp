#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <boost/shared_ptr.hpp>
#include <libtcod.h>

class Map;

class Entity
{
public:
	typedef boost::shared_ptr<Entity> ShPtr;
	
	int x;
	int y;
	char c;
	Map* host_map;
	TCODColor color;

	Entity(Map* host_map, int x, int y, int c, TCODColor color);
	~Entity();

	bool move(int x, int y);

	void draw(TCODConsole* console);
};

#endif
