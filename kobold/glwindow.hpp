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
	virtual void set_scale(float x, float y, float z);
	void set_texture(unsigned int t);
	bool is_shown();
	void show();
	void hide();

protected:
	static unsigned int id_;
	Mesh::ShPtr mesh_;
	unsigned int texture_index_;
	Vector3f::ShPtr position_;
	Vector3f::ShPtr scale_;

private:
	std::vector<Vector3f> colors_;
	bool visible_;

	DISALLOW_COPY_AND_ASSIGN(GlWindow);
};

#endif
