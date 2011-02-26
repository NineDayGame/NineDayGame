#ifndef NDG_FOVLISTENER_H_
#define NDG_FOVLISTENER_H_

#include <libtcod.hpp>

class FovListener
{
public:
	virtual void update_view(int x, int y, bool seen_before, char c, TCODColor color, bool transparent, bool walkable) = 0;
};

#endif
