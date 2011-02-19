#include <libtcod.hpp>
#include "map.hpp"

Map::Map(int w, int h)
{
	width = w;
	height = h;
	data = new TCODMap(w,h);
	display = new ConsoleDisplay[w*h];
}

Map::~Map()
{
	delete data;
	delete[] display;
}

void Map::draw(TCODConsole* console)
{
	for(int y = 0; y < height; ++y)
	{
		for(int x = 0; x < width; ++x)
		{
			char c = display[x+y*width].c;
			TCODColor color = display[x+y*width].color;
			console->setChar(x,y,c);
			console->setFore(x,y,color);
		}
	}
}

void Map::clear()
{
	for(int y = 0; y < height; ++y)
	{
		for(int x = 0; x < width; ++x)
		{
			data->setProperties(x,y,true,true);
			display[x+y*width].c = '.';
			display[x+y*width].color = TCOD_grey;
		}
	}
}
