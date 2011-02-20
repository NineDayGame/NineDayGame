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

	host_map->data->setProperties(x,y,false,false);
}

Entity::~Entity()
{

}

bool Entity::move(int _x, int _y)
{
	if(host_map->data->isWalkable(_x,_y))
	{
		bool transp = host_map->data->isTransparent(x,y);
		host_map->data->setProperties(x,y,transp,true);

		x = _x;
		y = _y;

		host_map->data->setProperties(x,y,false,false);
		return true;
	}
	return false;
}

void Entity::draw(TCODConsole* console)
{
	console->setChar(x,y,c);
	console->setFore(x,y,color);
}
