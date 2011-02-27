#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <boost/shared_ptr.hpp>
#include <libtcod.hpp>
#include <list>
#include <string>
#include "printable.hpp"
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

class TextCamera : public Camera, public Printable
{
public:
	typedef boost::shared_ptr<TextCamera> ShPtr;

	std::list<std::string> text;

	TextCamera(int sx, int sy, int w, int h);
	virtual ~TextCamera();

	virtual void draw();
	virtual void print(const std::string s);
};

class TargetingCamera : public Camera
{
public:
	typedef boost::shared_ptr<TargetingCamera> ShPtr;
	
	Map::WkPtr map;
	Entity::ShPtr player;
	int x;
	int y;

	TargetingCamera(Map::WkPtr m, Entity::ShPtr e, int tx, int ty, int sx, int sy, int w, int h);
	virtual ~TargetingCamera();

	virtual void draw();
	virtual void move(int x, int y);
};

#endif
