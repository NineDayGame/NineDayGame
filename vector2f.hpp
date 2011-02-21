#ifndef NDG_VECTOR2F_H_
#define NDG_VECTOR2F_H_

#include <boost/shared_ptr.hpp>

#include "basetypes.hpp"

// Basic object for representing a vertex in 3 dimensions
class Vector2f {
public: 
	typedef boost::shared_ptr<Vector2f> ShPtr;
  
	float u_, v_;
  
	Vector2f(float, float);
  
private:
	//DISALLOW_COPY_AND_ASSIGN(Vector2f);
};

#endif
