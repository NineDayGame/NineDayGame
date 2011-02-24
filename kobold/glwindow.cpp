#include "glwindow.hpp"
#include "rect.hpp"
#include "vector3f.hpp"

GlWindow::GlWindow()
  : texture_index_(0),
    visible_(false) {
	init();
}

void GlWindow::init() {
	mesh_.reset(new Rect());
	set_color(Vector3f(1.0f, 1.0f, 1.0f));
}

void GlWindow::draw() {
	if (visible_) {
		glPushMatrix();
		glLoadIdentity();
		glTranslatef(position_->x, position_->y, 0.0f);
		glScalef(scale_->x, scale_->y, 0.0f);
		
		glBindTexture(GL_TEXTURE_2D, texture_index_);
		mesh_->draw();
		glColorPointer(3, GL_FLOAT, 0, &colors_[0]);
		
		glDrawArrays(GL_TRIANGLES, 0, mesh_->triangle_count() * 3);
		
		glPopMatrix();
	}
}

void GlWindow::set_color(Vector3f color) {
	colors_.clear();
	for (int i = 0; i < (mesh_->triangle_count() * 3); ++i) {
		colors_.push_back(color);
	}
}

void GlWindow::set_position(float x, float y, float z) {
	position_.reset(new Vector3f(x, y, z));
}

void GlWindow::set_scale(float x, float y, float z) {
	scale_.reset(new Vector3f(x, y, z));
}

void GlWindow::set_texture(unsigned int t) {
	texture_index_ = t;
}

bool GlWindow::is_shown() {
	return visible_;
}

void GlWindow::show() {
	visible_ = true;
}

void GlWindow::hide() {
	visible_ = false;
}
