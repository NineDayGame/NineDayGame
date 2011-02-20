#ifndef NDG_VERTEX_H_
#define NDG_VERTEX_H_

#include <boost/shared_ptr.hpp>

#include "basetypes.hpp"

// Basic object for representing a vertex in 3 dimensions
class Vertex {
public: 
	typedef boost::shared_ptr<Vertex> ShPtr;
  
	float x_, y_, z_;
  
	Vertex(float, float, float);
  
private:
	//DISALLOW_COPY_AND_ASSIGN(Vertex);
};

#endif
