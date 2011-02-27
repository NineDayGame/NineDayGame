#include "goblin_targetstate.hpp"

GoblinTargetState::GoblinTargetState(GameState::ShPtr p, TargetingCamera::ShPtr c, Living::ShPtr e, std::string a, TargetCallback cb) : GameState(p), camera(c), player(e), callback(cb), action(a)
{
	
}

GoblinTargetState::~GoblinTargetState()
{

}

void GoblinTargetState::handle_input()
{
	TCODConsole::flush();
	TCOD_key_t key = TCODConsole::waitForKeypress(true);
	int x = camera->x;
	int y = camera->y;

	if(TCODConsole::isWindowClosed()) { GameState::running = false; return; }
	if(key.vk == TCODK_ESCAPE) { GameState::state = parent; return; }
	if(key.vk == TCODK_KP8) { --y; }
	if(key.vk == TCODK_KP2) { ++y; }
	if(key.vk == TCODK_KP4) { --x; }
	if(key.vk == TCODK_KP6) { ++x; }
	if(key.vk == TCODK_KP7) { --x; --y; }
	if(key.vk == TCODK_KP9) { ++x; --y; }
	if(key.vk == TCODK_KP1) { --x; ++y; } 
	if(key.vk == TCODK_KP3) { ++x; ++y; }
	camera->move(x,y);

	if(key.vk == TCODK_ENTER || key.vk == TCODK_KPENTER)
	{
		if(callback)
		{
			Living::ShPtr p = SCONVERT(Living,Entity,player.lock());
			(*callback)(p,action,x,y);
		}
		GameState::state = parent->parent;
	}
}

void GoblinTargetState::draw()
{
	GameState::draw();
	camera->draw();
}

