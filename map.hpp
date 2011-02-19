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
	}  ConsoleDisplay;

public:
	int width;
	int height;
	TCODMap* data;
	ConsoleDisplay* display;
	
	Map(int width, int height);
	~Map();

	void draw(TCODConsole* console);
	void clear();

};

#endif
