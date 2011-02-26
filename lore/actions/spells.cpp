#include "living.hpp"
#include "action_scheduler.hpp"

void Living::init_spells()
{
	REGISTER_ACTION(heal,"Heal",500,TARGET_LIVING);
	REGISTER_ACTION(shield,"Shield",500,TARGET_LIVING);
	REGISTER_ACTION(haste,"Haste",500,TARGET_LIVING);
	REGISTER_ACTION(flaming_hands,"Flaming Hands",500,TARGET_DIRECTION);
	REGISTER_ACTION(drain_life,"Drain Life",500,TARGET_LIVING);
}

void Living::heal(ActionArgs args)
{
	SCHEDULE_ACTION();
	cprintf("%s",__FUNCTION__);
}

void Living::shield(ActionArgs args)
{
	SCHEDULE_ACTION();
	cprintf("%s",__FUNCTION__);
}

void Living::haste(ActionArgs args)
{
	SCHEDULE_ACTION();
	cprintf("%s",__FUNCTION__);
}

	
void Living::flaming_hands(ActionArgs args)
{
	SCHEDULE_ACTION();
	cprintf("%s",__FUNCTION__);
}

void Living::drain_life(ActionArgs args)
{
	SCHEDULE_ACTION();
	cprintf("%s",__FUNCTION__);
}
