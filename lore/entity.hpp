#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <list>
#include <libtcod.hpp>
#include "container.hpp"

class Map;

class Entity : public Container
{
public:
	typedef boost::shared_ptr<Entity> ShPtr;
	typedef boost::weak_ptr<Entity> WkPtr;

	typedef void (*FOVCallback)(int x, int y, bool seen_before, char c, TCODColor color, bool transparent, bool walkable);
	
	int x;
	int y;
	int z;
	char c;
	TCODColor color;

	int sight_range;
	std::list<Entity::WkPtr> seen;

	boost::weak_ptr<Map> host_map;
	boost::shared_ptr<Map> known_map;

	Entity(boost::weak_ptr<Map> host_map, int x, int y, int c, TCODColor color);
	virtual ~Entity();

	virtual bool move(int x, int y);
	virtual void look();

	void register_fovcb(Entity::FOVCallback cb);

protected:
	Entity::FOVCallback fov_cb;
};

#endif
