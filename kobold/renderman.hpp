#ifndef NDG_RENDERMAN_H_
#define NDG_RENDERMAN_H_

#include <boost/shared_ptr.hpp>

#include "entity.hpp"
#include "glrenderer.hpp"
#include "util.hpp"

/*
 * RenderMan, in theory, is used as an abstraction layer between different rendering systems like OpenGL or 
 * DirectX. In practice, however, since we only have plans to develop an OpenGL renderer, this file is just a
 * useless extra layer of redirection.
 */
class RenderMan {
public:
	typedef boost::shared_ptr<RenderMan> ShPtr;

	RenderMan();
	void init();
	
	void add_movable(Movable::ShPtr movable);
	void add_window(GlWindow::ShPtr window);
	void clear_movables();
	void clear_windows();
	
	// TODO: This need to get out of RenderMan and in to game logic
	void set_player(float x, float y);
	
	void draw_frame();
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
