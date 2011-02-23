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
	
	float get_attenuation_constant();
	float get_attenuation_linear();
	float get_attenuation_quadratic();
	
	Vector3f::ShPtr get_position();
	Vector4f::ShPtr get_ambient();
	Vector4f::ShPtr get_diffuse();
	Vector4f::ShPtr get_specular();
	
	void set_attenuation_constant(float c);
	void set_attenuation_linear(float l);
	void set_attenuation_quadratic(float q);
	
	void set_position(Vector3f::ShPtr pos);
	void set_ambient(Vector4f::ShPtr ambient);
	void set_diffuse(Vector4f::ShPtr linear);
	void set_specular(Vector4f::ShPtr spec);

	Light();
	void init();

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
