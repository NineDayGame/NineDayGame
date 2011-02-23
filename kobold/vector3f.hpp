#ifndef NDG_VECTOR3F_H_
#define NDG_VECTOR3F_H_

#include <boost/shared_ptr.hpp>

#include "util.hpp"

// Basic object for representing a vertex in 3 dimensions
class Vector3f {
public: 
	typedef boost::shared_ptr<Vector3f> ShPtr;
  
	float x, y, z;

	Vector3f(float xi, float yi, float zi);
	float length() const;
	float distance(const Vector3f& rhs) const;
  
private:
	//DISALLOW_COPY_AND_ASSIGN(Vector3f);
};

#endif
