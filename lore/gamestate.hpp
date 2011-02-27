#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <libtcod.hpp>

#include "living.hpp"

class GameState : public boost::enable_shared_from_this<GameState>
{
public:
	typedef boost::shared_ptr<GameState> ShPtr;
	
	static GameState::ShPtr state;
	static bool running;
	
	GameState::ShPtr parent;

	Living::ShPtr player;

	GameState(GameState::ShPtr p, Living::ShPtr e) : parent(p), player(e) {}
	virtual ~GameState() {}

	virtual void handle_input() = 0;
	virtual void draw() { if(parent) parent->draw(); }

	GameState::ShPtr get_first_parent() { if(parent) return parent->get_first_parent(); return this->shared_from_this(); }
protected:
	
};

#endif
