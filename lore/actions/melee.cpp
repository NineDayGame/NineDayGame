#include "living.hpp"
#include "action_scheduler.hpp"

void Living::init_melee()
{
	REGISTER_ACTION(spin_attack);
	REGISTER_ACTION(precise_strike);
	REGISTER_ACTION(giant_swing);
	REGISTER_ACTION(cripple);
}

// none
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

// Living
void Living::precise_strike(ActionArgs args)
{
	SCHEDULE_ACTION(500);
	cprintf("%s",__FUNCTION__);
}

// Living
void Living::giant_swing(ActionArgs args)
{
	SCHEDULE_ACTION(500);
	cprintf("%s",__FUNCTION__);
}

// Living
void Living::cripple(ActionArgs args)
{
	SCHEDULE_ACTION(500);
	cprintf("%s",__FUNCTION__);
}
