#ifndef ACTION_SCHEDULER_HPP
#define ACTION_SCHEDULER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/tuple/tuple.hpp>
#include <list>
#include <climits>
#include "living.hpp"
#include "util.hpp"

class ActionScheduler
{
public:
	typedef boost::shared_ptr<ActionScheduler> ShPtr;
	typedef boost::tuple<Living::ShPtr, std::string, int> Scheduled;

	std::list<Scheduled> ready;
	std::list<Scheduled> blocked;

	ActionScheduler() : smallest_tick(INT_MAX) {}
	~ActionScheduler() {}

	void schedule_action(Living::ShPtr character, std::string action, int energy_required);
	
	void tick();
	
protected:
	int smallest_tick;

	int new_smallest;
};

extern ActionScheduler as;

#endif
