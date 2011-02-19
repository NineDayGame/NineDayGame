#ifndef MAP_HPP
#define MAP_HPP

#include <libtcod.hpp>

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
	int width;
	int height;
	TCODMap* data;
	ConsoleDisplay* display;
	
	Map(int width, int height);
	~Map();

	void draw(TCODConsole* console);

	void set_data(int x, int y, char c, TCODColor color, bool transparent, bool walkable);
	void clear();

	void randomize(int num_rooms);
};

#endif
