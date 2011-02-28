#include <stdio.h>
#include <cmath>
#include "living.hpp"
#include "util.hpp"
#include "item.hpp"
#include "gamestate.hpp"

#include "action_scheduler.hpp"

Living::Living(Map::WkPtr host_map, std::string n, int x, int y, int c, TCODColor color, int _health) : Entity(host_map,x,y,c,color), health(_health), name(n),_rand(TCODRandom::getInstance()), action_energy(0), blocked(false), kill_count(0)
{
	z = 1;
	faction = 0;

	REGISTER_ACTION(test,"Test",0,10,TARGET_NONE);
	REGISTER_ACTION(attack,"Attack",0,150,TARGET_LIVING);
	REGISTER_ACTION(walk,"Walk",0,100,TARGET_PLACE);
	REGISTER_ACTION(pickup,"Pickup",0,50,TARGET_ITEM);
	REGISTER_ACTION(wait,"Wait",0,100,TARGET_NONE);

	init_melee();
	init_spells();
}

void Living::test(ActionArgs args)
{
	SCHEDULE_ACTION();
	cprintf("%s -> %s",__FUNCTION__,name.c_str());
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

void Living::gain_experience(int amount)
{
	experience += amount;
	if(experience >= 10*pow(2,level))
	{
		++level;
		IF_IN_VIEW(cprintf("%s gains a new level!",name.c_str()));
		str += rand(3);
		int _magic = rand(3);
		dex += rand(3);
		intel += rand(3);
		int _con = rand(3);
		int _soul = rand(3);
		disp += rand(3);
		if(_rand->getFloat(0,1) > 0.8f) speed += 0.01;

		max_health += _rand->getInt(_con,_con*4);
		max_mana += _rand->getInt(_magic+_soul,_magic*2+_soul*2);

		health = max_health;
		mana = max_mana;

		magic += _magic;
		con += _con;
		soul += _soul;
	}
}

void Living::walk(ActionArgs args)
{
	SCHEDULE_ACTION();
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
	CHECK_REQUIREMENTS();
	SCHEDULE_ACTION();
	Item::ShPtr e = SCONVERT(Item,void,args[0]);
	e->container.lock()->remove(e);
	get(e);

	IF_IN_VIEW(cprintf("%s gets %s.",name.c_str(),e->name.c_str()));
}

void Living::attack(ActionArgs args)
{
	CHECK_REQUIREMENTS();
	SCHEDULE_ACTION();
	Living::ShPtr e = SCONVERT(Living,void,args[0]);
	if(e)
	{
		if(melee_tohit() > e->dodge())
		{
			int damage = melee_damage();

			IF_IN_VIEW(cprintf("%s hit %s for %d damage.",name.c_str(),e->name.c_str(),damage));
			
			e->damage(this,damage);
		}		
	}
}

void Living::damage(Living* attacker, int damage)
{
	health -= damage;
	if(health <= 0)
	{
		die(attacker);
	}
}

void Living::die(Living* killer)
{
	IF_IN_VIEW(cprintf("%s killed %s!",killer->name.c_str(),name.c_str()));
	
	Map::ShPtr m = SCONVERT(Map,Container,container.lock());
	if(!m)
	{
		return;
	}

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

	++killer->kill_count;
	killer->gain_experience((10*max_health/killer->max_health));

	m->get_data(x,y,&c,&color,&trans,&walk);
	m->set_data(x,y,c,TCOD_red,true,true);
	m->remove(this->shared_from_this());
}

void Living::wait(ActionArgs args)
{
	SCHEDULE_ACTION();
}
