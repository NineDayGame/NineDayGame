#include "glwindow.hpp"
#include "rect.hpp"
#include "vector3f.hpp"

GlWindow::GlWindow()
  : texture_index_(0) {
	init();
}

void GlWindow::init() {
	mesh_.reset(new Rect());
	set_color(Vector3f(1.0f, 1.0f, 1.0f));
}

void GlWindow::draw() {
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(128, 0, 0);
	glScalef(256, 100, 0);
	
	glBindTexture(GL_TEXTURE_2D, texture_index_);
	mesh_->draw();
	glColorPointer(3, GL_FLOAT, 0, &colors_[0]);
	
	glDrawArrays(GL_TRIANGLES, 0, mesh_->triangle_count() * 3);
	
	glPopMatrix();
}

/*void GlWindow::update() {
	//a_ += 1.0f;
}*/

void GlWindow::set_color(Vector3f color) {
	colors_.clear();
	for (int i = 0; i < (mesh_->triangle_count() * 3); ++i) {
		colors_.push_back(color);
	}
}

void GlWindow::set_position(float x, float y, float z) {
	x_ = x;
	y_ = y;
	z_ = z;
}

void GlWindow::set_scale3f(float x, float y, float z) {
	sx_ = x;
	sy_ = y;
	sz_ = z;
}

void GlWindow::set_texture(unsigned int t) {
	texture_index_ = t;
}
