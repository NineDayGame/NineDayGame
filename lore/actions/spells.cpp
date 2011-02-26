#include "living.hpp"
#include "action_scheduler.hpp"

void Living::init_spells()
{
	REGISTER_ACTION(heal);
	REGISTER_ACTION(shield);
	REGISTER_ACTION(haste);
	REGISTER_ACTION(flaming_hands);
	REGISTER_ACTION(drain_life);
}

void Living::heal(ActionArgs args)
{
	SCHEDULE_ACTION(500);
	cprintf("%s",__FUNCTION__);
}

void Living::shield(ActionArgs args)
{
	SCHEDULE_ACTION(500);
	cprintf("%s",__FUNCTION__);
}

void Living::haste(ActionArgs args)
{
	SCHEDULE_ACTION(500);
	cprintf("%s",__FUNCTION__);
}

	
void Living::flaming_hands(ActionArgs args)
{
	SCHEDULE_ACTION(500);
	cprintf("%s",__FUNCTION__);
}

void Living::drain_life(ActionArgs args)
{
	SCHEDULE_ACTION(500);
	cprintf("%s",__FUNCTION__);
}
