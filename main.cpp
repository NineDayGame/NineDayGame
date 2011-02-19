#include <libtcod.hpp>

int main(int argc, char* argv[])
{
	TCODConsole::initRoot(80,50,"Test",false);
	while(!TCODConsole::isWindowClosed())
	{
		TCODConsole::flush();
		TCOD_key_t key=TCODConsole::waitForKeypress(true);
		if(key.vk == TCODK_ESCAPE) { break; }
	}

	return 0;
}
