#include <libtcod.hpp>
#include "camera.hpp"
#include "util.hpp"

Camera::Camera(int sx, int sy, int w, int h) : screen_x(sx), screen_y(sy), width(w), height(h)
{

}

Camera::~Camera()
{

}
void Camera::draw()
{
	TCODConsole::root->rect(screen_x,screen_y,width,height,true);
}

bool Camera::check_bounds(Map::ShPtr map, int x, int y)
{
	if(x < screen_x || x > screen_x+width) return false;
	if(y < screen_y || y > screen_y+height) return false;
	if(x < 0 || x > TCODConsole::root->getWidth()) return false;
	if(y < 0 || y > TCODConsole::root->getHeight()) return false;
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

void EntityCamera::draw()
{
	Camera::draw();
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
			if(check_bounds(m,draw_x,draw_y))
			{
				char c = m->display[tx+ty*m->width].c;
				TCODColor color = m->display[tx+ty*m->width].color;
				TCODConsole::root->setChar(draw_x,draw_y,c);
				TCODConsole::root->setFore(draw_x,draw_y,color);
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
			if(check_bounds(m,draw_x,draw_y))
			{
				char c = e->c;
				TCODColor color = e->color;
				TCODConsole::root->setChar(draw_x,draw_y,c);
				TCODConsole::root->setFore(draw_x,draw_y,color);
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

void TextCamera::draw()
{
	Camera::draw();
	int i = 0;
	foreach(std::string s, text)
	{
		TCODConsole::root->printLeft(screen_x,screen_y+i,TCOD_BKGND_NONE,s.c_str());
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

TargetingCamera::TargetingCamera(Map::WkPtr m, Entity::ShPtr e, int tx, int ty, int sx, int sy, int w, int h)
	: Camera(sx,sy,w,h), player(e), map(m), x(tx), y(ty) {}
TargetingCamera::~TargetingCamera() {}

void TargetingCamera::draw()
{
	Camera::draw();
	TCODConsole* console = TCODConsole::root;

	Map::ShPtr m = map.lock();
	for(int j = -height/2; j < height/2; ++j)
	{
		for(int i = -width/2; i < width/2; ++i)
		{
			int tx = i+x;
			int ty = j+y;
			int draw_x = i+screen_x+width/2;
			int draw_y = j+screen_y+height/2;			
			if(check_bounds(m,draw_x,draw_y))
			{
				char c = m->display[tx+ty*m->width].c;
				TCODColor color = m->display[tx+ty*m->width].color;
				TCODConsole::root->setChar(draw_x,draw_y,c);
				TCODConsole::root->setFore(draw_x,draw_y,color);
			}
		}
	}

	player->look();
	player->seen.sort(compare_entities);
	foreach(Entity::WkPtr i, player->seen)
	{
		Entity::ShPtr e = i.lock();
		if(e)
		{
			int tx = e->x-x;
			int ty = e->y-y;
			int draw_x = screen_x+width/2+tx;
			int draw_y = screen_y+height/2+ty;
			if(check_bounds(m,draw_x,draw_y))
			{
				char c = e->c;
				TCODColor color = e->color;
				TCODConsole::root->setChar(draw_x,draw_y,c);
				TCODConsole::root->setFore(draw_x,draw_y,color);
			}
		}
	}
	
	int draw_x = screen_x+width/2;
	int draw_y = screen_y+height/2;	
	console->putChar(draw_x,draw_y,'X');
}

void TargetingCamera::move(int _x, int _y)
{	
	x = _x;
	y = _y;
}
