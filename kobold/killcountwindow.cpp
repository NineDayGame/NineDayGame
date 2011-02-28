#include <iostream>

#include <boost/lexical_cast.hpp>

#include "killcountwindow.hpp"

const int kFONT_HEIGHT = 8;

KillCountWindow::KillCountWindow() {
	init();
}

void KillCountWindow::init() {
	mesh_.reset(new Rect());
	set_color(Vector3f(1.0f, 1.0f, 1.0f));
}

void KillCountWindow::draw() {
	if (is_shown()) {
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, font_->get_texture()->get_index());
		glListBase(font_->get_displaylist());
		
		glLoadIdentity();
		glTranslatef(position_->x, position_->y, position_->z);
		glCallLists(kill_string_.size(), GL_BYTE, kill_string_.c_str());
		
		glPopMatrix();
	}
}

void KillCountWindow::update_kills(int kills) {
	kill_string_.clear();
	kill_string_ += "Kills: ";
	kill_string_ += boost::lexical_cast<std::string>(kills);
}

void KillCountWindow::set_font(Font::ShPtr font) {
	font_ = font;
}
