#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <boost/shared_ptr.hpp>
#include <libtcod.hpp>
#include "map.hpp"
#include "entity.hpp"

class Camera
{
public:
	typedef boost::shared_ptr<Camera> ShPtr;
	
	int screen_x;
	int screen_y;
	int width;
	int height;

	Map::WkPtr map;
	Entity::ShPtr target;

	Camera(Map::WkPtr map, Entity::ShPtr target, int sx, int sy, int w, int h);
	virtual ~Camera();

	void draw(TCODConsole* console);
};

#endif
