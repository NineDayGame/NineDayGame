#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <libtcod.hpp>

class GameState : public boost::enable_shared_from_this<GameState>
{
public:
	typedef boost::shared_ptr<GameState> ShPtr;
	
	static GameState::ShPtr state;
	
	GameState::ShPtr parent;

	GameState(GameState::ShPtr p) { parent = p; }
	virtual ~GameState() {}

	virtual void handle_key_press(TCOD_key_t key) = 0;
	virtual void draw(TCODConsole* console) { if(parent) parent->draw(console); }
};

#endif
