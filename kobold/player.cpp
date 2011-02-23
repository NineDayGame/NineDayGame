#include <iostream>

#include "player.hpp"
#include "vector3f.hpp"

Player::Player()
  : sight_radius_(0.0f) {
	init();
}

void Player::init() {
	mesh_.reset(new Cube());
	set_color(Vector3f(0.5f, 0.0f, 0.0f));
	Light::ShPtr light (new Light());
	light_ = light;
}

void Player::set_position(float x, float y, float z) {
	Movable::set_position(x, y, z);
	Vector3f::ShPtr pos (new Vector3f(x, y, z));
	//std::cout << "Setting light pos: " << x << ", " << y << ", " << z;
	light_->set_position(pos);
}

const float Player::get_sight_radius() const {
	return sight_radius_;
}

void Player::set_sight_radius(float r) {
	sight_radius_ = r;
}

Light::ShPtr Player::get_light() {
	return light_;
}
