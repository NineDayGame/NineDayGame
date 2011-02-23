#include "item.hpp"
#include "map.hpp"

Item::Item(boost::weak_ptr<Map> host_map, std::string n, std::string desc, int x, int y, int c, TCODColor color) : Entity(host_map,x,y,c,color), name(n), description(desc)
{
}

Item::~Item()
{

}
