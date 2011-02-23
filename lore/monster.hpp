#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <boost/shared_ptr.hpp>
#include "living.hpp"
#include "ai.hpp"
#include "map.hpp"

class Monster : public Living, public AI
{
public:
	typedef boost::shared_ptr<Monster> ShPtr;
	
	Monster(Map::WkPtr host_map, std::string name, int x, int y, int c, TCODColor color, int health);
	virtual ~Monster();
	
	virtual void ai();
};

#endif
