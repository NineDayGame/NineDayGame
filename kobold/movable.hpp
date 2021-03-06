#ifndef NDG_MOVABLE_H_
#define NDG_MOVABLE_H_

#include <boost/shared_ptr.hpp>
#include <vector>

#include "util.hpp"
//#include "cube.hpp"

#include "mesh.hpp"
#include "vector3f.hpp"

class Movable {
public:
	typedef boost::shared_ptr<Movable> ShPtr;
	
	Movable();
	//virtual void init();
	virtual void draw();
	void update();
	const Vector3f::ShPtr get_position() const;
	void set_color(Vector3f color);
	virtual void set_position(float x, float y, float z);
	void set_rotation(float a, float b, float c);
	void set_scale3f(float x, float y, float z);
	void set_texture(unsigned int t);

protected:
	Mesh::ShPtr mesh_;
	std::vector<Vector3f> colors_;
	float x_, y_, z_;
	float rx_, ry_, rz_;
	float sx_, sy_, sz_;

private:
	unsigned int texture_index_;
	DISALLOW_COPY_AND_ASSIGN(Movable);
};

#endif
