#include "player.hpp"
#include "vertex.hpp"

Player::Player() {
	init();
}

void Player::init() {
	mesh_.reset(new Cube());
	set_color(Vertex(0.5f, 0.0f, 0.0f));
}
