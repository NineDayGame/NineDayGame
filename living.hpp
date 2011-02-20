#ifndef LIVING_HPP
#define LIVING_HPP
#include <boost/shared_ptr.hpp>
#include <libtcod.hpp>
#include "entity.hpp"
#include "map.hpp"

class Living : public Entity
{
public:
	typedef boost::shared_ptr<Living> ShPtr;
	
	int health;

	Living(Map::WkPtr host_map, int x, int y, int c, TCODColor color, int health);
	virtual ~Living();
	virtual bool move(int x, int y);
	virtual bool attack(boost::shared_ptr<Living> e);

	virtual void die();
};

#endif
