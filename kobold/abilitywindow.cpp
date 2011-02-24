#include <iostream>

#include <boost/lexical_cast.hpp>

#include "abilitywindow.hpp"

const int kLINE_COUNT = 10;
const int kFONT_HEIGHT = 8;

AbilityWindow::AbilityWindow() {
	init();
}

void AbilityWindow::init() {
	abilities_.reset(new std::string[kLINE_COUNT]);
	mesh_.reset(new Rect());
	set_color(Vector3f(1.0f, 1.0f, 1.0f));
}

void AbilityWindow::draw() {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture_index_);
    glListBase(dl_index_);
    
    for (int i = 0; i < kLINE_COUNT; ++i) {
		glLoadIdentity();
		glTranslatef(position_->x, position_->y+kFONT_HEIGHT*(kLINE_COUNT-(i+1)), position_->z);
		//std::cout << "draw " << console_[i].size() << " ";
		glCallLists(abilities_[i].size(), GL_BYTE, abilities_[i].c_str());
	}
	
	glPopMatrix();
}

void AbilityWindow::set_ability(std::string ability, int index) {
	ability.insert(0, boost::lexical_cast<std::string>(index));
	if (index >= 10) {
		ability.insert(2, " ");
	} else {
		ability.insert(1, "  ");
	}
	abilities_[index-1] = ability;
}

void AbilityWindow::set_dl_index(int dl_index) {
	dl_index_ = dl_index;
}
