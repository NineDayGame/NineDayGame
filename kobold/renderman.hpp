#ifndef NDG_RENDERMAN_H_
#define NDG_RENDERMAN_H_

#include <boost/shared_ptr.hpp>

#include "entity.hpp"
#include "glrenderer.hpp"
#include "util.hpp"

class RenderMan {
public:
	typedef boost::shared_ptr<RenderMan> ShPtr;

	RenderMan();
	void init();
	void draw_frame();
	void reload_world();
	void set_entity(Entity::ShPtr entity);
	void take_screenshot();
	void toggle_fullscreen();
	void toggle_lighting();
	void toggle_wireframes();

private:
	GlRenderer::ShPtr renderer_;
	Entity::ShPtr e_;
	int ssCount_;
	
	DISALLOW_COPY_AND_ASSIGN(RenderMan);
};

#endif
