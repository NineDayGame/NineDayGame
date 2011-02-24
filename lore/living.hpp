#ifndef LIVING_HPP
#define LIVING_HPP
#include <boost/shared_ptr.hpp>
#include <libtcod.hpp>
#include <string>
#include "entity.hpp"
#include "map.hpp"
#include "util.hpp"

class Living : public Entity
{
public:
	typedef boost::shared_ptr<Living> ShPtr;

	std::string name;

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
	int speed;

	int melee_tohit() { return rand(str/4 + dex); }
	int melee_damage() { return rand(str)+1; }
	int dodge() { return rand(dex); }

	Living(Map::WkPtr host_map, std::string name, int x, int y, int c, TCODColor color, int health);
	virtual ~Living();

	virtual void init_stats(int str, int magic, int dex, int intel, int con, int soul, int disp, int speed);
	
	virtual bool move(int x, int y);
	virtual bool attack(boost::shared_ptr<Living> e);

	virtual void die(Living* killer);
protected:
	TCODRandom* _rand;
	virtual int rand(int x) { return _rand->getInt(0,x); }
};

#endif
