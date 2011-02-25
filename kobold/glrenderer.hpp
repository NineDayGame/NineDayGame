#ifndef NDG_GLRENDERER_HPP_
#define NDG_GLRENDERER_HPP_

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <string>
#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "character.hpp"
#include "entity.hpp"
#include "map.hpp"
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
	void add_window(GlWindow::ShPtr window);
	void load_map(const Map& map);
	void load_mobs(std::list<Entity::WkPtr> mobs);
	void printgl(std::string output);
	void set_light(int index, const Light& light);
	void set_sight_radius(float r);
	void take_screenshot(std::string filename);
	void toggle_fullscreen();
	void toggle_lighting();
	void toggle_wireframes();
	void set_player(float x, float y);
	void render();

private:
	GlConsoleWindow::ShPtr cwindow_;
	AbilityWindow::ShPtr ability_window_;
	HealthWindow::ShPtr health_window_;
	MenuWindow::ShPtr menu_window_;
	/*GlWindow::ShPtr sheet_window_;
	GlWindow::ShPtr inventory_window_;*/
	Timer::ShPtr fps_;
	std::vector<Movable::ShPtr> movables_;
	std::list<GlWindow::ShPtr> windows_;
	TextureMan::ShPtr texman_;
	FontMan::ShPtr fontman_;
	
	Player::ShPtr player_;
	SDL_Surface* sdlSurface_;
	float cameraX_, cameraY_, cameraZ_;
	float lightX_, lightY_, lightZ_;
	bool lights_, wireframes_;
	int dl_index_;
	
	DISALLOW_COPY_AND_ASSIGN(GlRenderer);
};

#endif
