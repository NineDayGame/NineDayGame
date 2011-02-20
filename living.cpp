#include <stdio.h>
#include "living.hpp"

Living::Living(Map::WkPtr host_map, int x, int y, int c, TCODColor color, int _health) : Entity(host_map,x,y,c,color), health(_health)
{

}

Living::~Living()
{

}

bool Living::move(int x, int y)
{	
	if(!Entity::move(x,y))
	{
		for(std::list<Entity::WkPtr>::iterator i = seen.begin(); i != seen.end(); ++i)
		{
			Living::ShPtr e = boost::static_pointer_cast<Living,Entity>((*i).lock());
			if(e->x == x && e->y == y)
			{
				attack(e);
			}
		}
	}
}

bool Living::attack(Living::ShPtr e)
{
	e->health--;
	if(e->health <= 0)
	{
		e->die();
	}
}

void Living::die()
{
	Map::ShPtr m = host_map.lock();
	m->data->setProperties(x,y,true,true);
	m->remove_entity(this->shared_from_this());
}