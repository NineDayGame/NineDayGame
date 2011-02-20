#include <libtcod.hpp>
#include "map.hpp"
#include "entity.hpp"

Entity::Entity(boost::weak_ptr<Map> _host_map, int _x, int _y, int _c, TCODColor _color)
{
	host_map = _host_map;
	x = _x;
	y = _y;
	c = _c;
	color = _color;
	sight_range = 7;

	host_map.lock()->data->setProperties(x,y,false,false);
	known_map = Map::ShPtr(new Map(host_map.lock()->width,host_map.lock()->height));
}

Entity::~Entity()
{
	host_map.lock()->data->setProperties(x,y,true,true);
}

bool Entity::move(int _x, int _y)
{
	if(host_map.lock()->data->isWalkable(_x,_y))
	{
		bool transp = host_map.lock()->data->isTransparent(x,y);
		bool transp2 = host_map.lock()->data->isTransparent(_x,_y);
		host_map.lock()->data->setProperties(x,y,transp,true);

		x = _x;
		y = _y;

		host_map.lock()->data->setProperties(x,y,transp2,false);
		return true;
	}
	return false;
}

void Entity::look()
{
	host_map.lock()->data->computeFov(x,y,sight_range,true,FOV_PERMISSIVE_5);
	for(int i = -sight_range; i < sight_range; ++i)
	{
		for(int j = -sight_range; j < sight_range; ++j)
		{
			if(host_map.lock()->data->isInFov(x+i,y+j))
			{
				host_map.lock()->copy_data(known_map,x+i,y+j);
			}
		}
	}
	seen.clear();
	for(std::list<Entity::ShPtr>::iterator i = host_map.lock()->entities.begin(); i != host_map.lock()->entities.end(); ++i)
	{
		if(host_map.lock()->data->isInFov((*i)->x,(*i)->y))
		{
			seen.push_back(Entity::WkPtr(*i));
		}
	}
}

void Entity::draw(TCODConsole* console)
{
	console->setChar(x,y,c);
	console->setFore(x,y,color);
}

void Entity::draw_map(TCODConsole* console)
{
	known_map->draw(console);
	for(std::list<Entity::WkPtr>::iterator i = seen.begin(); i != seen.end(); ++i)
	{
		(*i).lock()->draw(console);
	}
}
