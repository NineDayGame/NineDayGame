#include <iostream>

#include <boost/lexical_cast.hpp>

#include "healthwindow.hpp"

const int kFONT_HEIGHT = 8;

HealthWindow::HealthWindow() {
	init();
}

void HealthWindow::init() {
	mesh_.reset(new Rect());
	set_color(Vector3f(1.0f, 1.0f, 1.0f));
}

void HealthWindow::draw() {
	if (is_shown()) {
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texture_index_);
		glListBase(dl_index_);
		
		glLoadIdentity();
		glTranslatef(position_->x, position_->y, position_->z);
		//std::cout << "draw " << console_[i].size() << " ";
		glCallLists(health_string_.size(), GL_BYTE, health_string_.c_str());
		
		glPopMatrix();
	}
}

void HealthWindow::update_health(int current, int max) {
	health_string_.clear();
	health_string_ += "HP: ";
	health_string_ += boost::lexical_cast<std::string>(current);
	health_string_ += "/";
	health_string_ += boost::lexical_cast<std::string>(max);
}

void HealthWindow::set_dl_index(int dl_index) {
	dl_index_ = dl_index;
}
