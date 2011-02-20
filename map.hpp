#ifndef MAP_HPP
#define MAP_HPP

#include <boost/shared_ptr.hpp>
#include <vector>
#include <libtcod.hpp>
#include "entity.hpp"

class Map
{
private:
	typedef struct
	{
		TCODColor color;
		char c;
	} ConsoleDisplay;

	typedef struct
	{
		int x;
		int y;
		int w;
		int h;
	} Room;

	void set_room_data(Map::Room r, char c, TCODColor color, bool transparent, bool walkable);

public:
	typedef boost::shared_ptr<Map> ShPtr;
	
	int width;
	int height;
	TCODMap* data;
	ConsoleDisplay* display;
	std::vector<Entity::ShPtr> entities;
	
	Map(int width, int height);
	~Map();

	void draw(TCODConsole* console);

	void set_data(int x, int y, char c, TCODColor color, bool transparent, bool walkable);
	void clear();

	void randomize(int num_rooms);
	void random_free_spot(int* x, int* y);

	void add_entity(Entity::ShPtr e);
};

#endif
