#ifndef NDG_VECTOR4F_H_
#define NDG_VECTOR4F_H_

#include <boost/shared_ptr.hpp>

#include "util.hpp"

// Basic object for representing a vertex in 4 dimensions
class Vector4f {
public: 
	typedef boost::shared_ptr<Vector4f> ShPtr;
  
	float w_, x_, y_, z_;
  
	Vector4f(float, float, float, float);
  
private:
	//DISALLOW_COPY_AND_ASSIGN(Vector4f);
};

#endif
