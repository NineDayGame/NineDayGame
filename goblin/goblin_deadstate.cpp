#include "goblin_deadstate.hpp"
#include <libtcod.hpp>

GoblinDeadState::GoblinDeadState(GameState::ShPtr parent, Living::ShPtr player) : GameState(parent,player) {}
GoblinDeadState::~GoblinDeadState() {}

void GoblinDeadState::handle_input()
{
	TCODConsole::flush();
	TCOD_key_t key = TCODConsole::waitForKeypress(true);
	if(key.vk == TCODK_ESCAPE)
	{
		GameState::running = false;
		GameState::state = parent;
	}
}
