#include "item.hpp"
#include "map.hpp"

Item::Item(boost::weak_ptr<Map> host_map, std::string n, std::string desc, int x, int y, int c, TCODColor color) : Entity(host_map,x,y,c,color), name(n), description(desc)
{
}

Item::~Item()
{

}

void Item::use(Living::ShPtr user)
{
	TCODRandom* r = TCODRandom::getInstance();
	int gain = r->getInt(1,10);
	user->health += gain;
	cprintf("%s uses the %s and regains %d health.",user->name.c_str(),name.c_str(),gain);
}
