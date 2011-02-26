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

	REGISTER_ACTION(test);
	REGISTER_ACTION(attack);
	REGISTER_ACTION(walk);
	REGISTER_ACTION(pickup);
	REGISTER_ACTION(wait);
	REGISTER_ACTION(spin_attack);
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

double Living::distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
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

void Living::walk(ActionArgs args)
{
	SCHEDULE_ACTION(10);
	boost::shared_ptr<int> _x = SCONVERT(int,void,args[0]);
	boost::shared_ptr<int> _y = SCONVERT(int,void,args[1]);
	if(!move(*_x,*_y))
	{
		foreach(Entity::WkPtr w, seen)
		{
			Living::ShPtr e = DCONVERT(Living,Entity,w.lock());
			if(e != NULL && e->x == *_x && e->y == *_y)
			{
				ActionArgs a;
				a.push_back(e);
				attack(a);
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
				ActionArgs a;
				a.push_back(e);
				pickup(a);
			}
		}
	}
}

void Living::pickup(ActionArgs args)
{
	SCHEDULE_ACTION(10);
	Item::ShPtr e = SCONVERT(Item,void,args[0]);
	e->container.lock()->remove(e);
	get(e);
	cprintf("%s gets %s.",name.c_str(),e->name.c_str());
}

void Living::attack(ActionArgs args)
{
	SCHEDULE_ACTION(100);
	Living::ShPtr e = SCONVERT(Living,void,args[0]);
	if(e)
	{
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

void Living::wait(ActionArgs args)
{
	SCHEDULE_ACTION(10);
}

void Living::spin_attack(ActionArgs args)
{
	SCHEDULE_ACTION(500);
	cprintf("%s performs a spin attack!",name.c_str());
	std::list<Living::ShPtr> to_attack;
	foreach(Entity::WkPtr e, seen)
	{
		Living::ShPtr l = SCONVERT(Living,Entity,e.lock());
		if(l && l.get() != this && l->health > 0 && distance(x,y,l->x,l->y) < 2)
		{
			to_attack.push_back(l);
		}
	}
	action_energy += to_attack.size() * 100/speed;
	foreach(Living::ShPtr e, to_attack)
	{
		ActionArgs a;
		a.push_back(e);
		attack(a);
	}
}
