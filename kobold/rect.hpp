#ifndef NDG_RECT_H_
#define NDG_RECT_H_

#include <boost/shared_ptr.hpp>

#include "util.hpp"
#include "mesh.hpp"

class Rect : public Mesh {
public:
	typedef boost::shared_ptr<Rect> ShPtr;

	Rect();
	void init();
	int triangle_count();

private:
	DISALLOW_COPY_AND_ASSIGN(Rect);
};

#endif
