#ifndef AI_HPP
#define AI_HPP

#include <boost/shared_ptr.hpp>
#include <libtcod.hpp>

#include "map.hpp"

class AI
{
public:
	typedef boost::shared_ptr<AI> ShPtr;

	AI(Map::ShPtr m) : path(new TCODPath(m->data,1.41f)) {}
	virtual ~AI() {}

	boost::shared_ptr<TCODPath> path;
	virtual void ai() = 0;
};

#endif
