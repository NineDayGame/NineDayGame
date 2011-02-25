#ifndef LIVING_HPP
#define LIVING_HPP
#include <boost/shared_ptr.hpp>
#include <boost/unordered_map.hpp>
#include <boost/tuple/tuple.hpp>
#include <libtcod.hpp>
#include <string>
#include <vector>
#include "entity.hpp"
#include "map.hpp"
#include "util.hpp"

// Schedules the action to run when the Living gets enough energy.
// *** This will only work in functions inside of a Living-derived class ***
// This assumes the ActionArgs for the function is called args
#define SCHEDULE_ACTION(energy)                 \
	last_args = args;                           \
	if(action_energy < (energy)/speed)          \
	{                                           \
		blocked = true;                         \
		Living::ShPtr l = SCONVERT(Living,Container,this->shared_from_this()); \
		as.schedule_action(l,__FUNCTION__,(energy)/speed); \
		return;                                 \
	}                                           \
	else                                        \
	{                                           \
		blocked = false;                        \
		action_energy -= (energy)/speed;        \
	}

#define REGISTER_ACTION(action)           \
	{                                           \
		typedef typeof(*this) T;                \
		actions[#action] = static_cast<Living::Action>(&T::action); \
	}

class Living : public Entity
{
public:
	typedef boost::shared_ptr<Living> ShPtr;
	typedef std::vector<boost::shared_ptr<void> > ActionArgs;
	typedef void (Living::*Action)(ActionArgs args);
	
	boost::unordered_map<std::string, Living::Action> actions;
	ActionArgs last_args;

	std::string name;

	int faction;

	int max_health;
	int max_mana;
	
	int health;
	int mana;

	int str;
	int magic;
	int dex;
	int intel;
	int con;
	int soul;
	int disp;
	float speed;

	bool blocked;
	int action_energy;

	int melee_tohit() { return rand(str/4 + dex); }
	int melee_damage() { return rand(str)+1; }
	int dodge() { return rand(dex); }

	Living(Map::WkPtr host_map, std::string name, int x, int y, int c, TCODColor color, int health);
	virtual ~Living();

	virtual void init_stats(int str, int magic, int dex, int intel, int con, int soul, int disp, int speed);
	
	virtual void walk(ActionArgs args);
	virtual void attack(ActionArgs args);
	virtual void pickup(ActionArgs args);
	
	void test(ActionArgs args);

	virtual void die(Living* killer);
protected:
	TCODRandom* _rand;
	virtual int rand(int x) { return _rand->getInt(0,x); }
};

#endif
