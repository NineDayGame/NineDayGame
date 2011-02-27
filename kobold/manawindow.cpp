#include <iostream>

#include <boost/lexical_cast.hpp>

#include "manawindow.hpp"

const int kFONT_HEIGHT = 8;

ManaWindow::ManaWindow() {
	init();
}

void ManaWindow::init() {
	mesh_.reset(new Rect());
	set_color(Vector3f(1.0f, 1.0f, 1.0f));
}

void ManaWindow::draw() {
	if (is_shown()) {
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, font_->get_texture()->get_index());
		glListBase(font_->get_displaylist());
		
		glLoadIdentity();
		glTranslatef(position_->x, position_->y, position_->z);
		glCallLists(mana_string_.size(), GL_BYTE, mana_string_.c_str());
		
		glPopMatrix();
	}
}

void ManaWindow::update_mana(int current, int max) {
	mana_string_.clear();
	mana_string_ += "MP: ";
	mana_string_ += boost::lexical_cast<std::string>(current);
	mana_string_ += "/";
	mana_string_ += boost::lexical_cast<std::string>(max);
}

void ManaWindow::set_font(Font::ShPtr font) {
	font_ = font;
}
