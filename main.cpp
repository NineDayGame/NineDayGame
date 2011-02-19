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
	while(!TCODConsole::isWindowClosed())
	{
		m.draw(TCODConsole::root);
		TCODConsole::flush();
		TCOD_key_t key=TCODConsole::waitForKeypress(true);
		if(key.vk == TCODK_ESCAPE) { break; }
		if(key.vk == TCODK_SPACE) { m.randomize(10); }
	}

	return 0;
}
