#ifndef KOBOLD_DEADSTATE_HPP
#define KOBOLD_DEADSTATE_HPP

#include "gamestate.hpp"

class KoboldDeadState : public GameState
{
public:
	typedef boost::shared_ptr<KoboldDeadState> ShPtr;

	KoboldDeadState(GameState::ShPtr parent, Living::ShPtr player);
	virtual ~KoboldDeadState();

	virtual void handle_input();
};

#endif
