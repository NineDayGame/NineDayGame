#include <libtcod.hpp>
#include "camera.hpp"

Camera::Camera(Map::WkPtr m, Entity::WkPtr e, int sx, int sy, int w, int h) : map(m), target(e), screen_x(sx), screen_y(sy), width(w), height(h)
{

}

Camera::~Camera()
{

}

void Camera::draw(TCODConsole* console)
{
	Entity::ShPtr t = target.lock();
	Map::ShPtr m = map.lock();
	for(int y = -height/2; y < height/2; ++y)
	{
		for(int x = -width/2; x < width/2; ++x)
		{
			int tx = t->x+x;
			int ty = t->y+y;
			char c = m->display[tx+ty*m->width].c;
			TCODColor color = m->display[tx+ty*m->width].color;			
			console->setChar(x+screen_x+width/2,y+screen_y+height/2,c);
			console->setFore(x+screen_x+width/2,y+screen_y+height/2,color);
		}
	}
	for(std::list<Entity::WkPtr>::iterator i = t->seen.begin(); i != t->seen.end(); ++i)
	{
		Entity::ShPtr e = (*i).lock();
		int tx = e->x-t->x;
		int ty = e->y-t->y;
		char c = e->c;
		TCODColor color = e->color;
		console->setChar(screen_x+width/2+tx,screen_y+height/2+ty,c);
		console->setFore(screen_x+width/2+tx,screen_y+height/2+ty,color);
	}
}
