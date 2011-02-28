#ifndef GOBLIN_DEADSTATE_HPP
#define GOBLIN_DEADSTATE_HPP

#include "gamestate.hpp"

class GoblinDeadState : public GameState
{
public:
	typedef boost::shared_ptr<GoblinDeadState> ShPtr;

	GoblinDeadState(GameState::ShPtr parent, Living::ShPtr player);
	virtual ~GoblinDeadState();

	virtual void handle_input();
};

#endif
