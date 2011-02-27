#include "living.hpp"
#include "action_scheduler.hpp"

void Living::init_spells()
{
	REGISTER_ACTION(heal,"Heal",5,200,TARGET_LIVING);
	REGISTER_ACTION(shield,"Shield",10,300,TARGET_LIVING);
	REGISTER_ACTION(haste,"Haste",20,500,TARGET_LIVING);
	REGISTER_ACTION(flaming_hands,"Flaming Hands",5,300,TARGET_DIRECTION);
	REGISTER_ACTION(drain_life,"Drain Life",10,300,TARGET_LIVING);
}

void Living::heal(ActionArgs args)
{
	CHECK_REQUIREMENTS();
	SCHEDULE_ACTION();
	mana -= THIS_ACTION_INFO(ACTION_MANA);

	Living::ShPtr target = SCONVERT(Living,void,args[0]);
	int heal = rand(20);
	target->health += heal;
	if(target->health > target->max_health)
	{
		target->health = target->max_health;
	}
	
	cprintf("%s heals %d damage for %s.",name.c_str(),heal,target->name.c_str());
}

void Living::shield(ActionArgs args)
{
	CHECK_REQUIREMENTS();
	SCHEDULE_ACTION();
	mana -= THIS_ACTION_INFO(ACTION_MANA);
	cprintf("%s",__FUNCTION__);
}

void Living::haste(ActionArgs args)
{
	CHECK_REQUIREMENTS();
	SCHEDULE_ACTION();
	mana -= THIS_ACTION_INFO(ACTION_MANA);
	cprintf("%s",__FUNCTION__);
}
	
void Living::flaming_hands(ActionArgs args)
{
	CHECK_REQUIREMENTS();
	SCHEDULE_ACTION();
	mana -= THIS_ACTION_INFO(ACTION_MANA);
	boost::shared_ptr<double> angle = SCONVERT(double,void,args[0]);
	cprintf("%s casts Flaming Hands.",name.c_str());

	char c;
	TCODColor color;
	bool trans;
	bool walk;

	int radius = 4;
	std::list<Living::ShPtr> hit;
	for(double a = (-3.14/4)+*angle; a < (3.14/4)+*angle; a += 0.1)
	{
		for(int i = 0; i < radius; ++i)
		{
			int sx = x+i*cos(a);
			int sy = y+i*sin(a);
			foreach(Container::ShPtr c, container.lock()->inventory)
			{
				Living::ShPtr e = DCONVERT(Living,Container,c);
				if(e && e.get() != this && e->x == sx && e->y == sy)
				{
					hit.push_back(e);
				}
			}
		}
	}
	hit.sort();
	hit.unique();
	foreach(Living::ShPtr e, hit)
	{
		cprintf("The flames char %s.",e->name.c_str());
		e->damage(this,20);
	}
}

void Living::drain_life(ActionArgs args)
{
	CHECK_REQUIREMENTS();
	SCHEDULE_ACTION();
	mana -= THIS_ACTION_INFO(ACTION_MANA);
	cprintf("%s",__FUNCTION__);
}