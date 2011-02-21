#ifndef NDG_GLRENDERER_HPP_
#define NDG_GLRENDERER_HPP_

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <string>
#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "basetypes.hpp"
#include "character.hpp"
#include "entity.hpp"
#include "map.hpp"
#include "movable.hpp"
#include "player.hpp"
#include "timer.hpp"

class GlRenderer {
public:
	typedef boost::shared_ptr<GlRenderer> ShPtr;
	
	GlRenderer();
	void init();
	void init_gl();
	void load_map(const Map& map);
	void load_mobs(std::list<Entity::WkPtr> mobs);
	void take_screenshot(std::string filename);
	void update();
	void set_player(float x, float y);
	void render();

private:
	Timer::ShPtr fps_;
	std::vector<Movable::ShPtr> movables_;
	Player::ShPtr player_;
	SDL_Surface* sdlSurface_;
	
	DISALLOW_COPY_AND_ASSIGN(GlRenderer);
};

#endif
