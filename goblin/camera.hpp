#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <boost/shared_ptr.hpp>
#include <libtcod.hpp>
#include <list>
#include <string>
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

	Camera(int sx, int sy, int w, int h);
	virtual ~Camera();

	virtual void draw();
protected:
	bool check_bounds(Map::ShPtr map, int x, int y);
};

class EntityCamera : public Camera
{
public:
	typedef boost::shared_ptr<EntityCamera> ShPtr;
	
	Map::WkPtr map;
	Entity::ShPtr target;

	EntityCamera(Map::WkPtr map, Entity::ShPtr target, int sx, int sy, int w, int h);
	~EntityCamera();

	virtual void draw();
};

class TextCamera : public Camera
{
public:
	typedef boost::shared_ptr<TextCamera> ShPtr;

	std::list<std::string> text;

	TextCamera(int sx, int sy, int w, int h);
	virtual ~TextCamera();

	virtual void draw();
	virtual void print(const std::string s);
};

#endif
