#include <stdio.h>
#include <cmath>
#include "living.hpp"
#include "util.hpp"
#include "item.hpp"

#include "action_scheduler.hpp"

Living::Living(Map::WkPtr host_map, std::string n, int x, int y, int c, TCODColor color, int _health) : Entity(host_map,x,y,c,color), health(_health), name(n),_rand(TCODRandom::getInstance()), action_energy(0), blocked(false)
{
	z = 1;
	faction = 0;

	actions["test"] = &Living::test;
	actions["attack"] = &Living::attack;
}

void Living::test(ActionArgs args)
{
	SCHEDULE_ACTION(100);
	Living::ShPtr s = SCONVERT(Living,void,(args[0]));
	cprintf("%s -> %s",__FUNCTION__,s->name.c_str());
}

Living::~Living()
{

}

void Living::init_stats(int _str, int _magic, int _dex, int _intel, int _con, int _soul, int _disp, int _speed)
{
	str = _str;
	magic = _magic;
	dex = _dex;
	intel = _intel;
	con = _con;
	soul = _soul;
	disp = _disp;
	speed = _speed;

	max_health = _rand->getInt(con,con*4);
	max_mana = _rand->getInt(magic+soul,magic*2+soul*2);

	health = max_health;
	mana = max_mana;
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
				ActionArgs args;
				args.push_back(e);
				attack(args);
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

void Living::attack(ActionArgs args)
{
	SCHEDULE_ACTION(100);
	Living::ShPtr e = SCONVERT(Living,void,args[0]);
	if(melee_tohit() > e->dodge())
	{
		int damage = melee_damage();
		e->health -= damage;
		cprintf("%s hit %s for %d damage.",name.c_str(),e->name.c_str(),damage);
	}
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
	int radius = _rand->getInt(0,6);

	char c;
	TCODColor color;
	bool trans;
	bool walk;

	int splatter_range = _rand->getInt(1,6);
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
