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
