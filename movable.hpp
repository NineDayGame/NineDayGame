#ifndef NDG_MOVABLE_H_
#define NDG_MOVABLE_H_

#include <boost/shared_ptr.hpp>
#include <vector>

#include "basetypes.hpp"
#include "cube.hpp"

#include "mesh.hpp"
#include "vertex.hpp"

class Movable {
public:
	typedef boost::shared_ptr<Movable> ShPtr;
	
	Movable();
	//virtual void init();
	void draw();
	void update();
	void set_position(float x, float y, float z);
	void set_rotation(float a, float b, float c);
	void set_scale3f(float x, float y, float z);

protected:
	Mesh::ShPtr mesh_;
	std::vector<Vertex> colors_;
	float x_, y_, z_;
	float a_, b_, c_, d_;
	float sx_, sy_, sz_;

private:	
	DISALLOW_COPY_AND_ASSIGN(Movable);
};

#endif