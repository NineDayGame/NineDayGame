#include <libtcod.hpp>
#include "map.hpp"
#include "entity.hpp"

Entity::Entity(Map* _host_map, int _x, int _y, int _c, TCODColor _color)
{
	host_map = _host_map;
	x = _x;
	y = _y;
	c = _c;
	color = _color;
	sight_range = 7;

	host_map->data->setProperties(x,y,false,false);
	known_map = Map::ShPtr(new Map(host_map->width,host_map->height));
}

Entity::~Entity()
{

}

bool Entity::move(int _x, int _y)
{
	if(host_map->data->isWalkable(_x,_y))
	{
		bool transp = host_map->data->isTransparent(x,y);
		bool transp2 = host_map->data->isTransparent(_x,_y);
		host_map->data->setProperties(x,y,transp,true);

		x = _x;
		y = _y;

		host_map->data->setProperties(x,y,transp2,false);
		return true;
	}
	return false;
}

void Entity::look()
{
	host_map->data->computeFov(x,y,sight_range,true,FOV_PERMISSIVE_5);
	for(int i = -sight_range; i < sight_range; ++i)
	{
		for(int j = -sight_range; j < sight_range; ++j)
		{
			if(host_map->data->isInFov(x+i,y+j))
			{
				host_map->copy_data(known_map,x+i,y+j);
			}
		}
	}
	known_map->entities.clear();
	for(std::vector<Entity::ShPtr>::iterator i = host_map->entities.begin(); i != host_map->entities.end(); ++i)
	{
		if(host_map->data->isInFov((*i)->x,(*i)->y))
		{
			known_map->add_entity(*i);
		}
	}
}

void Entity::draw(TCODConsole* console)
{
	console->setChar(x,y,c);
	console->setFore(x,y,color);
}
