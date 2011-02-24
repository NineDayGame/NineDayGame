#include <libtcod.hpp>
#include "map.hpp"
#include "entity.hpp"
#include "util.hpp"

Entity::Entity(boost::weak_ptr<Map> _host_map, int _x, int _y, int _c, TCODColor _color)
{
	host_map = _host_map;
	x = _x;
	y = _y;
	z = 0;
	c = _c;
	color = _color;
	sight_range = 7;

	host_map.lock()->data->setProperties(x,y,false,false);
	known_map = Map::ShPtr(new Map(host_map.lock()->width,host_map.lock()->height));
	known_map->clear();
}

Entity::~Entity()
{
	
}

bool Entity::move(int _x, int _y)
{
	Map::ShPtr host = SCONVERT(Map,Container,container.lock());
	if(_x < 0 || _x > host->width || _y < 0 || _y > host->height)
	{
		return false;
	}
	
	if(host->data->isWalkable(_x,_y))
	{
		bool transp = host->data->isTransparent(x,y);
		bool transp2 = host->data->isTransparent(_x,_y);
		host->data->setProperties(x,y,transp,true);

		x = _x;
		y = _y;

		host->data->setProperties(x,y,transp2,false);
		return true;
	}
	return false;
}

void Entity::look()
{
	Map::ShPtr host = SCONVERT(Map,Container,container.lock());
	host->data->computeFov(x,y,sight_range,true,FOV_PERMISSIVE_5);
	for(int i = -sight_range; i < sight_range; ++i)
	{
		for(int j = -sight_range; j < sight_range; ++j)
		{
			if(host->data->isInFov(x+i,y+j))
			{
				host->copy_data(known_map,x+i,y+j);
			}
		}
	}
	seen.clear();
	foreach(Container::ShPtr i, host->inventory)
	{
		Entity::ShPtr e = SCONVERT(Entity,Container,i);
		if(host->data->isInFov(e->x,e->y))
		{
			seen.push_back(e);
		}
	}
}
