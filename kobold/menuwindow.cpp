#include <iostream>

#include <boost/lexical_cast.hpp>

#include "menuwindow.hpp"

const int kFONT_HEIGHT = 8;

MenuWindow::MenuWindow()
  : tail_(0),
    selected_(0) {
	init();
}

MenuWindow::~MenuWindow() {}

void MenuWindow::init() {
	mesh_.reset(new Rect());
	set_color(Vector3f(1.0f, 1.0f, 1.0f));
}

void MenuWindow::draw() {
	if (is_shown()) {
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, font_->get_texture()->get_index());
		glListBase(font_->get_displaylist());
				
		for (int i = 0; i < tail_; ++i) {
			glLoadIdentity();
			glTranslatef(position_->x, position_->y+kFONT_HEIGHT*(item_max_-(i+1)), position_->z);
			//std::cout << "draw " << console_[i].size() << " ";
			glCallLists(items_[i].size(), GL_BYTE, items_[i].c_str());
			if (i == selected_) {
				glLoadIdentity();
				glTranslatef(position_->x, position_->y+kFONT_HEIGHT*(item_max_-(i+1)), position_->z);
				glCallLists(1, GL_BYTE, "*");
			}
		}
		
		glPopMatrix();
	}
}

void MenuWindow::clear_items() {
	item_max_ = (int)(scale_->y/kFONT_HEIGHT);
	items_.reset(new std::string[item_max_]);
}

void MenuWindow::set_scale(float x, float y, float z) {
	GlWindow::set_scale(x, y, z);
	clear_items();
}

void MenuWindow::handle_input() {}

void MenuWindow::push_item(std::string item) {
	if (tail_ >= item_max_) {
		std::cout << "Item " << item << " not added - menu full" << std::endl;
		return;
	}
	item.insert(0, "  ");

	items_[tail_++] = item;
}

void MenuWindow::set_font(Font::ShPtr font) {
	font_ = font;
}

void MenuWindow::select_next() {
	selected_ = (selected_ == (tail_-1)) ? (tail_-1) : selected_ + 1;
}

void MenuWindow::select_prev() {
	selected_ = (selected_ == 0) ? 0 : selected_ - 1;
}

int MenuWindow::get_selected_index() {
	return selected_;
}
