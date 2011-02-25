#include <iostream>
#include "glconsolewindow.hpp"

const int kLINE_COUNT = 15;
const int kFONT_HEIGHT = 8;

GlConsoleWindow::GlConsoleWindow()
  : top_(0) {
	init();
}

void GlConsoleWindow::init() {
	console_.reset(new std::string[kLINE_COUNT]);
	mesh_.reset(new Rect());
	set_color(Vector3f(1.0f, 1.0f, 1.0f));
}

void GlConsoleWindow::draw() {
	if (is_shown()) {
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, font_->get_texture()->get_index());
		glListBase(font_->get_displaylist());
		int lineno = (top_ == 0) ? kLINE_COUNT - 1 : top_ - 1;
		
		for (int i = 0; i < kLINE_COUNT; ++i) {
			glLoadIdentity();
			glTranslatef(0, i*kFONT_HEIGHT, 0);
			//std::cout << "draw " << console_[i].size() << " ";
			glCallLists(console_[lineno].size(), GL_BYTE, console_[lineno].c_str());
			lineno = (lineno == 0) ? kLINE_COUNT - 1 : lineno - 1;
		}
		
		glPopMatrix();
	}
}

void GlConsoleWindow::print(const std::string output) {
	console_[top_++] = output;
	if (top_ >= kLINE_COUNT) {
		top_ = 0;
	}
}

void GlConsoleWindow::set_font(Font::ShPtr font) {
	font_ = font;
}
