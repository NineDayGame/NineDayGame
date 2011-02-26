#ifndef NDG_GLCAMERA_H_
#define NDG_GLCAMERA_H_

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include "SDL/SDL_opengl.h"

#include "util.hpp"
#include "vector3f.hpp"
#include "vector4f.hpp"

class GlCamera {
public:
	typedef boost::shared_ptr<GlCamera> ShPtr;
	
	GlCamera();
	void init();
	void setup_camera() const;
	
	const Vector3f::ShPtr get_coords() const;
	void set_coords(float x, float y);
	const Vector3f::ShPtr get_position() const;
	void set_position(Vector3f::ShPtr pos);

private:

	Vector3f::ShPtr coords_;
	Vector3f::ShPtr position_;

	DISALLOW_COPY_AND_ASSIGN(GlCamera);
};

#endif
