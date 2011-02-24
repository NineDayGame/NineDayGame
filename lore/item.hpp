#ifndef ITEM_HPP
#define ITEM_HPP

#include <boost/shared_ptr.hpp>
#include <string>
#include "entity.hpp"
#include "living.hpp"

class Item : public Entity
{
public:
	typedef boost::shared_ptr<Item> ShPtr;

	std::string name;
	std::string description;

	Item(boost::weak_ptr<Map> host_map, std::string name, std::string desc, int x, int y, int c, TCODColor color);
	virtual ~Item();

	virtual void use(Living::ShPtr user);
};

#endif
