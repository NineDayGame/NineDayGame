#include "font.hpp"

Font::Font(std::string name)
  : displaylist_(0),
    name_(name) { }

const std::string Font::get_name() const {
	return name_;
}

const bool Font::is_name(const std::string& rhs) const {
	return name_.compare(rhs) == 0;
}

const int Font::get_displaylist() const {
	return displaylist_;
}

void Font::set_displaylist(int index) {
	displaylist_ = index;
}

const Texture::ShPtr Font::get_texture() const {
	return texture_;
}

void Font::set_texture(Texture::ShPtr tex) {
	texture_ = tex;
}
