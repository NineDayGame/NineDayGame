#ifndef MAP_HPP
#define MAP_HPP

#include <boost/shared_ptr.hpp>
#include <list>
#include <libtcod.hpp>
#include "container.hpp"

class Entity;

class Map : public Container
{
protected:
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
	typedef boost::weak_ptr<Map> WkPtr;
	
	int width;
	int height;
	TCODMap* data;
	ConsoleDisplay* display;
	
	Map(int width, int height);
	~Map();

	void get_data(int x, int y, char* c, TCODColor* color, bool* transparent, bool* walkable);
	void set_data(int x, int y, char c, TCODColor color, bool transparent, bool walkable);
	void copy_data(Map::ShPtr m, int x, int y);
	void clear();

	void randomize(int num_rooms);
	void random_free_spot(int* x, int* y);

	bool check_bounds(int x, int y);
};

#endif
