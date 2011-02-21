#include <libtcod.hpp>
#include "camera.hpp"
#include "util.hpp"

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

Camera::Camera(int sx, int sy, int w, int h) : screen_x(sx), screen_y(sy), width(w), height(h)
{

}

Camera::~Camera()
{

}
void Camera::draw(TCODConsole* console)
{

}



EntityCamera::EntityCamera(Map::WkPtr m, Entity::ShPtr t, int sx, int sy, int w, int h) : map(m), target(t), Camera(sx,sy,w,h)
{

}

EntityCamera::~EntityCamera()
{

}

static bool compare_entities(Entity::WkPtr first, Entity::WkPtr second)
{
	return first.lock()->z < second.lock()->z;
}

void EntityCamera::draw(TCODConsole* console)
{
	Entity::ShPtr t = target;
	t->look();
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
	t->seen.sort(compare_entities);
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


TextCamera::TextCamera(int sx, int sy, int w, int h) : Camera(sx,sy,w,h)
{

}

TextCamera::~TextCamera()
{

}

void TextCamera::draw(TCODConsole* console)
{
	console->rect(screen_x,screen_y,width,height,true);
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
