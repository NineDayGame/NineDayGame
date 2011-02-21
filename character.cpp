#include "character.hpp"
#include "vertex.hpp"

Character::Character() {
	init();
}

void Character::init() {
	mesh_.reset(new Cube());
	set_color(Vertex(0.0f, 0.0f, 0.5f));
}
