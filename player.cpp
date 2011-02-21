#include "player.hpp"
#include "vertex.hpp"

Player::Player() {
	init();
}

void Player::init() {
	mesh_.reset(new Cube());
	
	for (int i = 0; i < (12 * 3); ++i) {
		colors_.push_back(Vertex(0.5f, 0.0f, 0.0f));
	}
}

void Player::update_position(float x, float y) {
	set_position(x + x_, y + y_, z_);
}
