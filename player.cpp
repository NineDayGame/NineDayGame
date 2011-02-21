#include "player.hpp"
#include "vector3f.hpp"

Player::Player() {
	init();
}

void Player::init() {
	mesh_.reset(new Cube());
	set_color(Vector3f(0.5f, 0.0f, 0.0f));
}
