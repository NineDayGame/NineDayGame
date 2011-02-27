#include "living.hpp"
#include "action_scheduler.hpp"

void Living::init_melee()
{
	REGISTER_ACTION(spin_attack,"Spin Attack",5,500,TARGET_NONE);
	REGISTER_ACTION(precise_strike,"Precise Strike",5,300,TARGET_LIVING);
	REGISTER_ACTION(giant_swing,"Giant Swing",5,300,TARGET_LIVING);
	REGISTER_ACTION(cripple,"Cripple",10,400,TARGET_LIVING);
}

// none
void Living::spin_attack(ActionArgs args)
{
	CHECK_REQUIREMENTS();
	SCHEDULE_ACTION();
	mana -= THIS_ACTION_INFO(ACTION_MANA);
	cprintf("%s performs a spin attack!",name.c_str());
	std::list<Living::ShPtr> to_attack;
	foreach(Entity::WkPtr e, seen)
	{
		Living::ShPtr l = DCONVERT(Living,Entity,e.lock());
		if(l && l.get() != this && l->health > 0 && distance(x,y,l->x,l->y) < 2)
		{
			to_attack.push_back(l);
		}
	}
	action_energy += to_attack.size() * actions_info["attack"].get<ACTION_ENERGY>()/speed;
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
	CHECK_REQUIREMENTS();
	
	Living::ShPtr target = SCONVERT(Living,void,args[0]);
	CHECK_RANGE(2);
	
	SCHEDULE_ACTION();
	mana -= THIS_ACTION_INFO(ACTION_MANA);

	cprintf("%s carefully watches for an opening in %s's defence, then attacks.",name.c_str(),target->name.c_str());

	action_energy += GET_ACTION_INFO(attack,ACTION_ENERGY)/speed;
	dex += 10;
	attack(args);
	dex -= 10;
}

// Living
void Living::giant_swing(ActionArgs args)
{
	CHECK_REQUIREMENTS();
	
	Living::ShPtr target = SCONVERT(Living,void,args[0]);
	CHECK_RANGE(2);
	
	SCHEDULE_ACTION();
	mana -= THIS_ACTION_INFO(ACTION_MANA);

	cprintf("%s takes a giant swing and attacks %s",name.c_str(),target->name.c_str());

	action_energy += GET_ACTION_INFO(attack,ACTION_ENERGY)/speed;
	str += 10;
	attack(args);
	str -= 10;
}

// Living
void Living::cripple(ActionArgs args)
{
	CHECK_REQUIREMENTS();
	Living::ShPtr l = SCONVERT(Living,void,args[0]);
	if(distance(x,y,l->x,l->y) >= 2)
	{
		cprintf("Target is not within range.");
		return;
	}
	SCHEDULE_ACTION();
	mana -= THIS_ACTION_INFO(ACTION_MANA);
	cprintf("%s",__FUNCTION__);
}
