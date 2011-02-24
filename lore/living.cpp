#include <stdio.h>
#include <cmath>
#include "living.hpp"
#include "util.hpp"
#include "item.hpp"

Living::Living(Map::WkPtr host_map, std::string n, int x, int y, int c, TCODColor color, int _health) : Entity(host_map,x,y,c,color), health(_health), name(n)
{
	z = 1;
}

Living::~Living()
{

}

bool Living::move(int x, int y)
{
	if(!Entity::move(x,y))
	{
		foreach(Entity::WkPtr w, seen)
		{
			Living::ShPtr e = DCONVERT(Living,Entity,w.lock());
			if(e != NULL && e->x == x && e->y == y)
			{
				attack(e);
			}
		}
	}
	else
	{
		foreach(Entity::WkPtr w, seen)
		{
			Item::ShPtr e = DCONVERT(Item,Entity,w.lock());
			if(e != NULL && e->x == x && e->y == y)
			{
				get(e);
				e->host_map.lock()->remove(e);
				cprintf("%s gets %s.",name.c_str(),e->name.c_str());
			}
		}
	}
}

bool Living::attack(Living::ShPtr e)
{
	e->health--;
	if(e->health <= 0)
	{
		e->die(this);
	}
}

void Living::die(Living* killer)
{
	cprintf("%s killed %s!",killer->name.c_str(),name.c_str());
	
	Map::ShPtr m = SCONVERT(Map,Container,container.lock());

	double angle = atan2((y-killer->y),(x-killer->x));
	TCODRandom* rand = TCODRandom::getInstance();
	int radius = rand->getInt(0,6);

	char c;
	TCODColor color;
	bool trans;
	bool walk;

	int splatter_range = rand->getInt(1,6);
	for(double a = (-3.14/splatter_range)+angle; a < (3.14/splatter_range)+angle; a += 0.1)
	{
		for(int i = 0; i < radius; ++i)
		{
			int sx = x+i*cos(a);
			int sy = y+i*sin(a);
			m->get_data(sx,sy,&c,&color,&trans,&walk);
			m->set_data(sx,sy,c,TCOD_red,trans,walk);
		}
	}

	foreach(Container::ShPtr c, inventory)
	{
		Item::ShPtr i = SCONVERT(Item,Container,c);
		i->x = x;
		i->y = y;
		m->get(i);
	}

	m->get_data(x,y,&c,&color,&trans,&walk);
	m->set_data(x,y,c,TCOD_red,true,true);
	m->remove(this->shared_from_this());
}
