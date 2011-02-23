#ifndef NDG_VECTOR4F_H_
#define NDG_VECTOR4F_H_

#include <boost/shared_ptr.hpp>

#include "util.hpp"

// Basic object for representing a vertex in 4 dimensions
class Vector4f {
public: 
	typedef boost::shared_ptr<Vector4f> ShPtr;
  
	float w, x, y, z;
  
	Vector4f(float wi, float xi, float yi, float zi);
  
private:
	//DISALLOW_COPY_AND_ASSIGN(Vector4f);
};

#endif
