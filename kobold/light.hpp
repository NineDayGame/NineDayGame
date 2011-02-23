#ifndef NDG_LIGHT_H_
#define NDG_LIGHT_H_

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include "movable.hpp"
#include "util.hpp"
#include "vector3f.hpp"
#include "vector4f.hpp"

class Light {
public:
	typedef boost::shared_ptr<Light> ShPtr;
	//static const Light NO_LIGHT;
	
	Light();
	void init();
	
	const float get_attenuation_constant() const;
	void set_attenuation_constant(float c);
	const float get_attenuation_linear() const;
	void set_attenuation_linear(float l);
	const float get_attenuation_quadratic() const;
	void set_attenuation_quadratic(float q);
	
	const Vector3f::ShPtr get_position() const;
	void set_position(Vector3f::ShPtr pos);
	const Vector4f::ShPtr get_ambient() const;
	void set_ambient(Vector4f::ShPtr ambient);
	const Vector4f::ShPtr get_diffuse() const;
	void set_diffuse(Vector4f::ShPtr linear);
	const Vector4f::ShPtr get_specular() const;
	void set_specular(Vector4f::ShPtr spec);

private:

	float attenuation_constant_;
	float attenuation_linear_;
	float attenuation_quadratic_;

	Vector3f::ShPtr position_;
	Vector4f::ShPtr ambient_;
	Vector4f::ShPtr diffuse_;
	Vector4f::ShPtr specular_;

	DISALLOW_COPY_AND_ASSIGN(Light);
};

#endif
