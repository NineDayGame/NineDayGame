#ifndef NDG_GLWINDOW_H_
#define NDG_GLWINDOW_H_

#include <boost/shared_ptr.hpp>

#include "mesh.hpp"
#include "util.hpp"
#include "vector3f.hpp"

class GlWindow {
public:
	typedef boost::shared_ptr<GlWindow> ShPtr;

	GlWindow();
	void init();
	virtual void draw();
	//void update();
	void set_color(Vector3f color);
	virtual void set_position(float x, float y, float z);
	void set_scale3f(float x, float y, float z);
	void set_texture(unsigned int t);

private:
	Mesh::ShPtr mesh_;
	std::vector<Vector3f> colors_;
	unsigned int texture_index_;

	float x_, y_, z_;
	float sx_, sy_, sz_;

	DISALLOW_COPY_AND_ASSIGN(GlWindow);
};

#endif
