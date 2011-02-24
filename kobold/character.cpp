#include "character.hpp"
#include "rect.hpp"
#include "vector3f.hpp"

Character::Character() {
	init();
}

void Character::init() {
	mesh_.reset(new Rect());
	set_color(Vector3f(0.0f, 0.0f, 0.5f));
	set_rotation(60.0f, -45.0f, -22.0f);
}

/*void Character::draw() {
	glBindTexture( GL_TEXTURE_2D, texture[0] );
	Movable::draw();
}*/
