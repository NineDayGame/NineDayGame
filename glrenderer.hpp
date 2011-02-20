#ifndef NDG_GLRENDERER_HPP_
#define NDG_GLRENDERER_HPP_

#include <boost/shared_ptr.hpp>
#include <vector>

#include "basetypes.hpp"
#include "movable.hpp"
#include "timer.hpp"

class GlRenderer {
public:
	typedef boost::shared_ptr<GlRenderer> ShPtr;
	
	GlRenderer();
	void init();
	void init_gl();
	void update();
	void render();

private:
	Timer::ShPtr fps_;
	std::vector<Movable::ShPtr> movables_;	
	
	DISALLOW_COPY_AND_ASSIGN(GlRenderer);
};

#endif
