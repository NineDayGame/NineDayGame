#ifndef NDG_RENDERMAN_H_
#define NDG_RENDERMAN_H_

#include <boost/shared_ptr.hpp>

#include "entity.hpp"
#include "glrenderer.hpp"
#include "util.hpp"
//----------------------------------------------
#include "textureman.hpp"
#include "fontman.hpp"
//----------------------------------------------

class RenderMan {
public:
	typedef boost::shared_ptr<RenderMan> ShPtr;

	RenderMan();
	void init();
	void draw_frame();
	void print_to_renderer(std::string output);
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

//----------------------------------------------
	GlConsoleWindow::ShPtr cwindow_;
	AbilityWindow::ShPtr ability_window_;
	HealthWindow::ShPtr health_window_;
	MenuWindow::ShPtr menu_window_;

	TextureMan::ShPtr texman_;
	FontMan::ShPtr fontman_;
//----------------------------------------------
	
	DISALLOW_COPY_AND_ASSIGN(RenderMan);
};

#endif
