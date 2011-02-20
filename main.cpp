#include <libtcod.hpp>
#include "map.hpp"

int main(int argc, char* argv[])
{
	int width = 120;
	int height = 80;
	TCODConsole::initRoot(width,height,"Test",false);

	Map m(width,height);
	m.clear();
	m.randomize(10);

	for(int i = 0; i < 5; ++i)
	{
		int x,y;
		m.random_free_spot(&x,&y);
		Entity::ShPtr e(new Entity(&m,x,y,'0'+i,TCOD_red));
		m.add_entity(e);
	}

	Entity::ShPtr e = m.entities[0];
	
	while(!TCODConsole::isWindowClosed())
	{
		m.draw(TCODConsole::root);
		TCODConsole::flush();
		TCOD_key_t key=TCODConsole::waitForKeypress(true);
		if(key.vk == TCODK_ESCAPE) { break; }
		if(key.vk == TCODK_SPACE) { m.randomize(10); }
		
		if(key.vk == TCODK_KP8) { e->move(e->x,e->y-1); }
		if(key.vk == TCODK_KP2) { e->move(e->x,e->y+1); }
		if(key.vk == TCODK_KP4) { e->move(e->x-1,e->y); }
		if(key.vk == TCODK_KP6) { e->move(e->x+1,e->y); }
		if(key.vk == TCODK_KP7) { e->move(e->x-1,e->y-1); }
		if(key.vk == TCODK_KP9) { e->move(e->x+1,e->y-1); }
		if(key.vk == TCODK_KP1) { e->move(e->x-1,e->y+1); }
		if(key.vk == TCODK_KP3) { e->move(e->x+1,e->y+1); }
	}

	return 0;
}
