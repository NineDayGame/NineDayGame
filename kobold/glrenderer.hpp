#ifndef NDG_GLRENDERER_HPP_
#define NDG_GLRENDERER_HPP_

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <list>
#include <string>
#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "glcamera.hpp"
#include "movable.hpp"
#include "player.hpp"
#include "fontman.hpp"
#include "textureman.hpp"
#include "timer.hpp"
#include "util.hpp"
#include "abilitywindow.hpp"
#include "glconsolewindow.hpp"
#include "glwindow.hpp"
#include "healthwindow.hpp"
#include "menuwindow.hpp"

class GlRenderer {
public:
	typedef boost::shared_ptr<GlRenderer> ShPtr;
	
	GlRenderer();
	void init();
	void init_gl();
	void set_camera(GlCamera::ShPtr camera);
	void set_dynamic_light(Light::ShPtr light);
	void add_movable(Movable::ShPtr movable);
	int add_window(GlWindow::ShPtr window);
	void clear_movables();
	void clear_windows();
	void remove_window(GlWindow::ShPtr window);
	void load_terrain(Movable::ShPtr movable);
	void set_ambient_light(const Vector4f& light);
	void set_light(int index, const Light& light);
	void take_screenshot(std::string filename);
	void toggle_fullscreen();
	void toggle_lighting();
	void toggle_wireframes();
	void render();

private:
	Timer::ShPtr fps_;
	std::vector<Movable::ShPtr> movables_;
	std::vector<Movable::ShPtr> terrain_;
	std::list<GlWindow::ShPtr> windows_;
	Light::ShPtr dynamic_light_;
	GlCamera::ShPtr camera_;

	// Required for screenshots and toggling between fullscreen and regular screen
	SDL_Surface* sdlSurface_;
	bool lights_, wireframes_;
	
	DISALLOW_COPY_AND_ASSIGN(GlRenderer);
};

#endif
