#include <iostream>

#include <boost/lexical_cast.hpp>

#include "abilitywindow.hpp"
#include "gamestate.hpp"

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
	glBindTexture(GL_TEXTURE_2D, font_->get_texture()->get_index());
	glListBase(font_->get_displaylist());
    
    for (int i = 0; i < kLINE_COUNT-1; ++i) {
	    std::string display;
	    display.insert(0, boost::lexical_cast<std::string>(i+1));
	    if (i+1 >= 10) {
		    display.insert(2, " ");
	    } else {
		    display.insert(1, "  ");
	    }
	    display += GameState::state->player->GET_ACTION_INFO(abilities_[i],ACTION_NAME);
	    
		glLoadIdentity();
		glTranslatef(position_->x, position_->y+kFONT_HEIGHT*(kLINE_COUNT-(i+1)), position_->z);
		glCallLists(display.size(), GL_BYTE, display.c_str());
	}
	
	glPopMatrix();
}

void AbilityWindow::set_ability(std::string ability, int index) {

	abilities_[index-1] = ability;
}

void AbilityWindow::set_font(Font::ShPtr font) {
	font_ = font;
}
