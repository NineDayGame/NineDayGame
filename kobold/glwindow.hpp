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
	void show();
	void hide();

protected:
	Mesh::ShPtr mesh_;
	unsigned int texture_index_;

private:
	std::vector<Vector3f> colors_;
	bool visible_;
	Vector3f::ShPtr position_;
	Vector3f::ShPtr scale_;

	DISALLOW_COPY_AND_ASSIGN(GlWindow);
};

#endif
