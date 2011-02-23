#ifndef NDG_PLAYER_H_
#define NDG_PLAYER_H_

#include <boost/shared_ptr.hpp>

#include "movable.hpp"
#include "light.hpp"
#include "util.hpp"

class Player : public Movable {
public:
	typedef boost::shared_ptr<Player> ShPtr;

	Player();
	void init();
	void set_position(float x, float y, float z);
	Light::ShPtr get_light();

private:
	Light::ShPtr light_;
	DISALLOW_COPY_AND_ASSIGN(Player);
};

#endif
