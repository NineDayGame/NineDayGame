#include <libtcod.hpp>
#include "camera.hpp"
#include "util.hpp"

Camera::Camera(int sx, int sy, int w, int h) : screen_x(sx), screen_y(sy), width(w), height(h)
{

}

Camera::~Camera()
{

}
void Camera::draw(TCODConsole* console)
{
	console->rect(screen_x,screen_y,width,height,true);
}

bool Camera::check_bounds(TCODConsole* console, Map::ShPtr map, int x, int y)
{
	if(x < screen_x || x > screen_x+width) return false;
	if(y < screen_y || y > screen_y+height) return false;
	if(x < 0 || x > console->getWidth()) return false;
	if(y < 0 || y > console->getHeight()) return false;
	if(x > map->width || y > map->height) return false;
	return true;
}

EntityCamera::EntityCamera(Map::WkPtr m, Entity::ShPtr t, int sx, int sy, int w, int h) : map(m), target(t), Camera(sx,sy,w,h)
{

}

EntityCamera::~EntityCamera()
{

}

static bool compare_entities(Entity::WkPtr first, Entity::WkPtr second)
{
	Entity::ShPtr f = first.lock();
	Entity::ShPtr s = second.lock();
	if(!f || !s) return false;
	return first.lock()->z < second.lock()->z;
}

void EntityCamera::draw(TCODConsole* console)
{
	Camera::draw(console);
	Entity::ShPtr t = target;
	Map::ShPtr m = map.lock();
	for(int y = -height/2; y < height/2; ++y)
	{
		for(int x = -width/2; x < width/2; ++x)
		{
			int tx = t->x+x;
			int ty = t->y+y;
			int draw_x = x+screen_x+width/2;
			int draw_y = y+screen_y+height/2;
			if(check_bounds(console,m,draw_x,draw_y))
			{
				char c = m->display[tx+ty*m->width].c;
				TCODColor color = m->display[tx+ty*m->width].color;
				console->setChar(draw_x,draw_y,c);
				console->setFore(draw_x,draw_y,color);
			}
		}
	}
	t->look();
	t->seen.sort(compare_entities);
	foreach(Entity::WkPtr i, t->seen)
	{
		Entity::ShPtr e = i.lock();
		if(e)
		{
			int tx = e->x-t->x;
			int ty = e->y-t->y;
			int draw_x = screen_x+width/2+tx;
			int draw_y = screen_y+height/2+ty;
			if(check_bounds(console,m,draw_x,draw_y))
			{
				char c = e->c;
				TCODColor color = e->color;
				console->setChar(draw_x,draw_y,c);
				console->setFore(draw_x,draw_y,color);
			}
		}
	}
}


TextCamera::TextCamera(int sx, int sy, int w, int h) : Camera(sx,sy,w,h)
{

}

TextCamera::~TextCamera()
{

}

void TextCamera::draw(TCODConsole* console)
{
	Camera::draw(console);
	int i = 0;
	foreach(std::string s, text)
	{
		console->printLeft(screen_x,screen_y+i,TCOD_BKGND_NONE,s.c_str());
		++i;
	}
}

void TextCamera::print(const std::string s)
{
	text.push_back(s);
	if(text.size() > height)
	{
		text.pop_front();
	}
}
