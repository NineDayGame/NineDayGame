#include <libtcod.hpp>
#include "map.hpp"
#include "entity.hpp"
#include "util.hpp"

Entity::Entity(boost::weak_ptr<Map> _host_map, int _x, int _y, int _c, TCODColor _color)
  : fovl_(0)
{
	host_map = _host_map;
	x = _x;
	y = _y;
	z = 0;
	c = _c;
	color = _color;
	sight_range = 7;
	//fov_cb = NULL;
	//fovl();

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
		host->data->setProperties(x,y,true,true);

		x = _x;
		y = _y;

		host->data->setProperties(x,y,false,false);
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
				char _c;
				TCODColor _color;
				bool _transparent;
				bool _walkable;
				bool seen_before = known_map->display[x+i + (y+j)*known_map->width].c != 0;
				host->get_data(x+i,y+j,&_c,&_color,&_transparent,&_walkable);
				known_map->set_data(x+i,y+j,_c,_color,_transparent,_walkable);
				
				//if(fov_cb) (*fov_cb)(x+i,y+j,seen_before,_c,_color,_transparent,_walkable);
				if (fovl_) {
					fovl_->update_view(x+i, y+j, seen_before, _c, _color, _transparent, _walkable);
				}
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

/*void Entity::register_fovcb(FovListener::ShPtr fovlistener)
{
	fovl = fovlistener;
}*/

void Entity::register_fovcb(FovListener* fovl)
{
	fovl_ = fovl;
}
