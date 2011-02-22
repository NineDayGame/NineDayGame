#ifndef NDG_VECTOR3F_H_
#define NDG_VECTOR3F_H_

#include <boost/shared_ptr.hpp>

#include "util.hpp"

// Basic object for representing a vertex in 3 dimensions
class Vector3f {
public: 
	typedef boost::shared_ptr<Vector3f> ShPtr;
  
	float x_, y_, z_;
  
	Vector3f(float, float, float);
  
private:
	//DISALLOW_COPY_AND_ASSIGN(Vector3f);
};

#endif
