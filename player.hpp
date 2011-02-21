#ifndef NDG_PLAYER_H_
#define NDG_PLAYER_H_

#include <boost/shared_ptr.hpp>

#include "basetypes.hpp"
#include "movable.hpp"

class Player : public Movable {
public:
	typedef boost::shared_ptr<Player> ShPtr;

	Player();
	void init();

private:
	DISALLOW_COPY_AND_ASSIGN(Player);
};

#endif
