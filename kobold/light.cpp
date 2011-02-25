#include "light.hpp"

Light::Light()
  : attenuation_constant_(1.0f),
    attenuation_linear_(0.0f),
    attenuation_quadratic_(0.0f),
    radius_(0.0f) {
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

const float Light::get_attenuation_constant() const {
	return attenuation_constant_;
}

void Light::set_attenuation_constant(float c) {
	attenuation_constant_ = c;
}

const float Light::get_attenuation_linear() const {
	return attenuation_linear_;
}

void Light::set_attenuation_linear(float l) {
	attenuation_linear_ = l;
}

const float Light::get_attenuation_quadratic() const {
	return attenuation_quadratic_;
}

void Light::set_attenuation_quadratic(float q) {
	attenuation_quadratic_ = q;
}

const float Light::get_radius() const {
	return radius_;
}

void Light::set_radius(float r) {
	radius_ = r;
}

const Vector3f::ShPtr Light::get_position() const {
	return position_;
}

void Light::set_position(Vector3f::ShPtr pos) {
	position_ = pos;
}

const Vector4f::ShPtr Light::get_ambient() const {
	return ambient_;
}

void Light::set_ambient(Vector4f::ShPtr ambient) {
	ambient_ = ambient;
}

const Vector4f::ShPtr Light::get_diffuse() const {
	return diffuse_;
}

void Light::set_diffuse(Vector4f::ShPtr diffuse) {
	diffuse_ = diffuse;
}

const Vector4f::ShPtr Light::get_specular() const {
	return specular_;
}

void Light::set_specular(Vector4f::ShPtr spec) {
	specular_ = spec;
}
