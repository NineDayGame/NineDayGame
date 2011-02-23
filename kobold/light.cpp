#include "light.hpp"

Light::Light()
  : attenuation_constant_(1.0f),
    attenuation_linear_(0.0f),
    attenuation_quadratic_(0.0f) {
	init();
}

void Light::init() {
	Vector3f::ShPtr pos (new Vector3f(0.0f, 0.0f, 0.0f));
	position_ = pos;
	Vector4f::ShPtr amb (new Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
	ambient_ = amb;
	Vector4f::ShPtr diff (new Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
	diffuse_ = diff;
	Vector4f::ShPtr spec (new Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
	specular_ = spec;
}

float Light::get_attenuation_constant() {
	return attenuation_constant_;
}

float Light::get_attenuation_linear() {
	return attenuation_linear_;
}

float Light::get_attenuation_quadratic() {
	return attenuation_quadratic_;
}

Vector3f::ShPtr Light::get_position() {
	return position_;
}

Vector4f::ShPtr Light::get_ambient() {
	return ambient_;
}

Vector4f::ShPtr Light::get_diffuse() {
	return diffuse_;
}

Vector4f::ShPtr Light::get_specular() {
	return specular_;
}

void Light::set_attenuation_constant(float c) {
	attenuation_constant_ = c;
}

void Light::set_attenuation_linear(float l) {
	attenuation_linear_ = l;
}

void Light::set_attenuation_quadratic(float q) {
	attenuation_quadratic_ = q;
}

void Light::set_position(Vector3f::ShPtr pos) {
	position_ = pos;
}

void Light::set_ambient(Vector4f::ShPtr ambient) {
	ambient_ = ambient;
}

void Light::set_diffuse(Vector4f::ShPtr diffuse) {
	diffuse_ = diffuse;
}

void Light::set_specular(Vector4f::ShPtr spec) {
	specular_ = spec;
}
