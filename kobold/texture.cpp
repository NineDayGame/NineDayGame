#include "texture.hpp"

Texture::Texture(std::string name)
  : texture_index_(0),
    name_(name) { }

const std::string Texture::get_name() const {
	return name_;
}

const bool Texture::is_name(const std::string& rhs) const {
	return name_.compare(rhs) == 0;
}

const int Texture::get_index() const {
	return texture_index_;
}

const int Texture::get_gltype() const {
	return gltype_;
}

const int Texture::get_bytecount() const {
	return bytecount_;
}

void Texture::set_index(int index) {
	texture_index_ = index;
}
