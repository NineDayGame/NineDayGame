#include "action_scheduler.hpp"

ActionScheduler as;

void ActionScheduler::schedule_action(Living::ShPtr character, std::string action, int energy_required)
{
	Scheduled s(character, action, energy_required);
	blocked.push_back(s);
	if(energy_required < smallest_tick)
	{
		smallest_tick = energy_required;
	}
}

static bool is_ready(const ActionScheduler::Scheduled s) { return s.get<0>()->action_energy >= s.get<2>(); }

void ActionScheduler::tick()
{
	while(ready.size() == 0 && blocked.size() > 0)
	{
		new_smallest = INT_MAX;
		//cprintf("Tick! %d",smallest_tick);
		foreach(Scheduled s, blocked)
		{
			Living::ShPtr l = s.get<0>();
			int ereq = s.get<2>();
			l->action_energy += smallest_tick;
			if(l->action_energy >= ereq)
			{
				ready.push_back(s);
			}
			else if(ereq - l->action_energy < new_smallest)
			{
				new_smallest = ereq - l->action_energy;
			}
		}
		if(new_smallest > smallest_tick) smallest_tick = new_smallest;
		blocked.remove_if(&is_ready);
	}
	foreach(Scheduled s, ready)
	{
		Living::ShPtr l = s.get<0>();
		std::string a = s.get<1>();
		Living::ActionArgs args = l->last_args.back();
		l->last_args.pop_back();
		((*l).*(l->actions[a]))(args);
	}
	ready.clear();
}
