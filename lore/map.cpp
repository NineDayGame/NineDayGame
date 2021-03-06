#include <libtcod.hpp>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include "map.hpp"
#include "entity.hpp"
#include "util.hpp"

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

bool Map::check_bounds(int x, int y)
{
	if(x < 0 || x > width) return false;
	if(y < 0 || y > height) return false;
	return true;
}

void Map::get_data(int x, int y, char* c, TCODColor* color, bool* transparent, bool* walkable)
{
	if(c) *c = display[x+y*width].c;
	if(color) *color = display[x+y*width].color;
	if(transparent) *transparent = data->isTransparent(x,y);
	if(walkable) *walkable = data->isWalkable(x,y);
}

void Map::set_data(int x, int y, char c, TCODColor color, bool transparent, bool walkable)
{
	if(check_bounds(x,y))
	{
		display[x+y*width].c = c;
		display[x+y*width].color = color;
		data->setProperties(x,y,transparent,walkable);
	}
}

void Map::copy_data(Map::ShPtr m, int x, int y)
{
	if(check_bounds(x,y) && m->check_bounds(x,y))
	{
		ConsoleDisplay cd = display[x+y*width];
		bool t = data->isTransparent(x,y);
		bool w = data->isWalkable(x,y);
		m->set_data(x,y,cd.c,cd.color,t,w);
	}
}

void Map::clear()
{
	for(int y = 0; y < height; ++y)
	{
		for(int x = 0; x < width; ++x)
		{
			data->setProperties(x,y,true,true);
			display[x+y*width].c = 0;
			display[x+y*width].color = TCOD_black;
		}
	}
}

void Map::set_room_data(Map::Room r, char c, TCODColor color, bool transparent, bool walkable)
{
	for(int y = r.y; y < r.y+r.h; ++y)
	{
		for(int x = r.x; x < r.x+r.h; ++x)
		{
			set_data(x,y,c,color,transparent,walkable);
		}
	}
}

void Map::randomize(int num_rooms)
{
	clear(); // Start with a blank map
	TCODRandom* rand = TCODRandom::getInstance();
	std::vector<Map::Room> rooms;
	for(int i = 0; i < num_rooms; ++i)
	{
		Map::Room r; // Randomly generate the dimensions for rectangular rooms
		r.x = rand->getInt(0,width-3);
		r.y = rand->getInt(0,height-3);
		r.w = rand->getInt(3,std::min(30,width-r.x-1));
		r.h = rand->getInt(3,std::min(30,height-r.y-1));
		rooms.push_back(r);

		// Draw the rooms as walls
		set_room_data(r,'#',TCOD_grey,false,false);
	}

	TCODPath path(data,0); // Prevent the pathfinder from making diagonal steps
	while(rooms.size() > 1)
	{
		Map::Room r1 = rooms.back(); rooms.pop_back();
		Map::Room r2 = rooms.back(); rooms.pop_back();

		// Make the rooms walkable so that pathfinding works
		set_room_data(r1,'.',TCOD_grey,true,true);
		set_room_data(r2,'.',TCOD_grey,true,true);

		// Pathfind from the centre of r1 to the centre of r2. This will be our hallway
		path.compute(r1.x+r1.w/2,r1.y+r1.h/2,r2.x+r2.w/2,r2.y+r2.h/2);
		while(!path.isEmpty())
		{
			int x,y;
			path.walk(&x,&y,true);
			set_data(x,y,'#',TCOD_grey,false,false);
		}

		// Set the rooms back to walls for now so that pathfinding goes around the room.
		set_room_data(r1,'#',TCOD_grey,false,false);
		set_room_data(r2,'#',TCOD_grey,false,false);
		
		// Add a room back into the mix so that all of the rooms get connected
		rooms.push_back(r2);
	}

	// Set walls to floor and floor to walls since we're done tricking the pathfinder
	for(int y = 0; y < height; ++y)
	{
		for(int x = 0; x < width; ++x)
		{
			if(data->isWalkable(x,y))
			{
				set_data(x,y,'#',TCOD_grey,false,false);
			}
			else
			{
				set_data(x,y,'.',TCOD_dark_green,true,true);
			}
		}
	}

	// Ensure there's a wall all the way around the map
	for(int x = 0; x < width; ++x)
	{
		set_data(x,0,'#',TCOD_grey,false,false);
		set_data(x,height-1,'#',TCOD_grey,false,false);
	}
	for(int y = 0; y < height; ++y)
	{
		set_data(0,y,'#',TCOD_grey,false,false);
		set_data(width-1,y,'#',TCOD_grey,false,false);
	}

	for(int i = 0; i < 4; ++i)
	{
		int x,y;
		random_free_spot(&x,&y);
		set_data(x,y,'<',TCOD_white,true,true);
	}
}

void Map::random_free_spot(int* x, int* y)
{
	TCODRandom* rand = TCODRandom::getInstance();
	do
	{
		*x = rand->getInt(0,width-1);
		*y = rand->getInt(0,height-1);
	} while(!data->isWalkable(*x,*y));
}
