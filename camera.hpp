#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <libtcod.hpp>
#include "map.hpp"
#include "entity.hpp"

class Camera
{
public:
	int screen_x;
	int screen_y;
	int width;
	int height;

	Map::WkPtr map;
	Entity::WkPtr target;

	Camera(Map::WkPtr map, Entity::WkPtr target, int sx, int sy, int w, int h);
	virtual ~Camera();

	void draw(TCODConsole* console);
};

#endif
