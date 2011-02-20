#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "movable.hpp"

Movable::Movable()
	: x_(0.0f), y_(0.0f), z_(0.0f),
	  a_(0.0f), b_(0.0f), c_(0.0f), d_(0.0f),
	  sx_(1.0f), sy_(1.0f), sz_(1.0f) {
}

void Movable::draw() {
	glPushMatrix();
	glTranslatef(x_, y_, 0.0f);
	//glRotatef(a_, 3.0f, 1.0f, d_);
	glScalef(sx_, sy_, sz_);
	
	mesh_->draw();
	glColorPointer(3, GL_FLOAT, 0, &colors_[0]);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	
	glPopMatrix();
}

void Movable::update() {
	//a_ += 1.0f;
}

void Movable::set_position(float x, float y, float z) {
	x_ = x;
	y_ = y;
	z_ = z;
}

void Movable::set_rotation(float a, float b, float c) {
	a_ = a;
	b_ = b;
	c_ = c;
}

void Movable::set_scale3f(float x, float y, float z) {
	sx_ = x;
	sy_ = y;
	sz_ = z;
}
