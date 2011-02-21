#include "character.hpp"
#include "vector3f.hpp"

Character::Character() {
	init();
}

void Character::init() {
	mesh_.reset(new Cube());
	set_color(Vector3f(0.0f, 0.0f, 0.5f));
}

/*void Character::draw() {
	glBindTexture( GL_TEXTURE_2D, texture[0] );
	Movable::draw();
}*/
