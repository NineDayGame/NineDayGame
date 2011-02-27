#include <iostream>

#include "glcamera.hpp"

GlCamera::GlCamera() {
	init();
}

void GlCamera::init() {
	position_.reset(new Vector3f(0.0f, 0.0f, 0.0f));
	coords_.reset(new Vector3f(0.0f, 0.0f, 0.0f));
}

void GlCamera::setup_camera() const {
	glTranslatef(position_->x, position_->y, position_->z);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(45.0f, -1.0f, 1.0f, 0.0f);
}

const Vector3f::ShPtr GlCamera::get_coords() const {
	return coords_;
}

void GlCamera::set_coords(float x, float y) {
	//std::cout << "Set camera " << x << " " << y << std::endl;
	position_.reset(new Vector3f(-0.7071f*x + 0.7071f*y, -0.5f*x + -0.5f*y, -25.0f + 0.5*x + 0.5f*y));
	coords_.reset(new Vector3f(x, y, 0.0f));
}

const Vector3f::ShPtr GlCamera::get_position() const {
	return position_;
}

void GlCamera::set_position(Vector3f::ShPtr pos) {
	position_ = pos; 
	// Not sure how to convert to coords. Better not call this!
}
