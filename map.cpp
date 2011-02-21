#include <libtcod.hpp>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include "map.hpp"
#include "entity.hpp"

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
	for(std::list<Entity::ShPtr>::iterator i = entities.begin(); i != entities.end(); ++i)
	{
		(*i)->draw(console);
	}
}

void Map::get_data(int x, int y, char* c, TCODColor* color, bool* transparent, bool* walkable)
{
	*c = display[x+y*width].c;
	*color = display[x+y*width].color;
	*transparent = data->isTransparent(x,y);
	*walkable = data->isWalkable(x,y);
}

void Map::set_data(int x, int y, char c, TCODColor color, bool transparent, bool walkable)
{
	display[x+y*width].c = c;
	display[x+y*width].color = color;
	data->setProperties(x,y,transparent,walkable);
}

void Map::copy_data(Map::ShPtr m, int x, int y)
{
	ConsoleDisplay cd = display[x+y*width];
	bool t = data->isTransparent(x,y);
	bool w = data->isWalkable(x,y);
	m->set_data(x,y,cd.c,cd.color,t,w);
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
		r.w = rand->getInt(3,std::min(10,width-r.x-1));
		r.h = rand->getInt(3,std::min(10,height-r.y-1));
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

void Map::add_entity(Entity* e)
{
	Entity::ShPtr p = boost::static_pointer_cast<Entity,Container>(e->shared_from_this());
	entities.push_back(p);
}

void Map::remove_entity(Entity* e)
{
	Entity::ShPtr p = boost::static_pointer_cast<Entity,Container>(e->shared_from_this());
	entities.remove(p);
}
