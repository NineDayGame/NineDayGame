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
#define SCHEDULE_ACTION()	  \
	{ \
		int energy = actions_info[__FUNCTION__].get<ACTION_ENERGY>(); \
		if(action_energy < energy/speed) \
		{ \
			last_args.push_back(args); \
			blocked = true; \
			Living::ShPtr l = SCONVERT(Living,Container,this->shared_from_this()); \
			as.schedule_action(l,__FUNCTION__,energy/speed); \
			return; \
		} \
		else \
		{ \
			blocked = false; \
			action_energy -= energy/speed; \
		} \
	}

#define REGISTER_ACTION(action,proper_name,mana_cost,energy_cost,target_type) \
	{                                           \
		typedef typeof(*this) T;                \
		actions[#action] = static_cast<Living::Action>(&T::action); \
		actions_info[#action] = ActionInfo(proper_name,mana_cost,energy_cost,target_type); \
	}

#define THIS_ACTION_INFO(type) actions_info[__FUNCTION__].get<(type)>()
#define GET_ACTION_INFO(action,type) actions_info[action].get<(type)>()

#define CHECK_REQUIREMENTS()	  \
	{ \
		int required_mana = actions_info[__FUNCTION__].get<ACTION_MANA>(); \
		ActionTargetType tt = actions_info[__FUNCTION__].get<ACTION_TARGET>(); \
		if(args.size() == 0 && tt != TARGET_NONE) \
		{ \
			cprintf("No target."); \
			return; \
		} \
		if(mana < required_mana) \
		{ \
			cprintf("Not enough mana."); \
			return; \
		} \
	}

#define CHECK_RANGE(range)	  \
	{ \
		if(distance(x,y,target->x,target->y) >= (range)) \
		{ \
			cprintf("Target is not within range."); \
			return; \
		} \
	}

// Only perform `do_this` if you're in sight of the player.
// Probably only useful for printing messages.
#define IF_IN_VIEW(do_this)	  \
	foreach(Entity::WkPtr c, GameState::state->player->seen) \
	{ \
		if(c.lock().get() == this) \
		{ \
			{ do_this; } \
			break; \
		} \
	} 		

#define ACTION_NAME 0
#define ACTION_MANA 1
#define ACTION_ENERGY 2
#define ACTION_TARGET 3

class Living : public Entity
{
public:
	typedef enum
	{
		TARGET_NONE,
		TARGET_LIVING,
		TARGET_ITEM,
		TARGET_PLACE,
		TARGET_DIRECTION,
	} ActionTargetType;
	
	typedef boost::shared_ptr<Living> ShPtr;
	typedef std::vector<boost::shared_ptr<void> > ActionArgs;
	typedef void (Living::*Action)(ActionArgs args);
	typedef boost::tuple<std::string/*proper name*/, int/*mana cost*/, int/*energy cost*/, ActionTargetType> ActionInfo;
	typedef boost::unordered_map<std::string, Living::Action> ActionMap;
	typedef boost::unordered_map<std::string, Living::ActionInfo> ActionInfoMap;
	
	ActionMap actions;
	ActionInfoMap actions_info;
	std::list<ActionArgs> last_args;

	std::string name;

	int faction;

	int level;
	int experience;
	int next_level;

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

	// Basic abilities
	virtual void walk(ActionArgs args); // x, y
	virtual void attack(ActionArgs args); // Living
	virtual void pickup(ActionArgs args); // Item
	virtual void wait(ActionArgs args); // none

	// Melee abilities
	virtual void spin_attack(ActionArgs args); // none
	virtual void precise_strike(ActionArgs args); // Living
	virtual void giant_swing(ActionArgs args); // Living
	virtual void cripple(ActionArgs args); // Living

	// Ranged abilities

	// Spells
	virtual void heal(ActionArgs args); // Living
	virtual void eagle_eye(ActionArgs args); // Living
	virtual void haste(ActionArgs args); // Living
	
	virtual void flaming_hands(ActionArgs args); // direction
	virtual void drain_life(ActionArgs args); // Living
	

	// Misc abilities
	void test(ActionArgs args); // none

	virtual void damage(Living* killer, int damage);
	virtual void die(Living* killer);
protected:
	TCODRandom* _rand;
	virtual int rand(int x) { return _rand->getInt(0,x); }

	//virtual void init_basic();
	virtual void init_melee();
	//virtual void init_ranged();
	virtual void init_spells();
	
};

#endif
