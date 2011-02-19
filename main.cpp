#include <libtcod.hpp>
#include "map.hpp"

int main(int argc, char* argv[])
{
	TCODConsole::initRoot(80,50,"Test",false);

	Map m(80,50);
	m.clear();
	while(!TCODConsole::isWindowClosed())
	{
		m.draw(TCODConsole::root);
		TCODConsole::flush();
		TCOD_key_t key=TCODConsole::waitForKeypress(true);
		if(key.vk == TCODK_ESCAPE) { break; }
	}

	return 0;
}
