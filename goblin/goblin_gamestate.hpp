#ifndef GOBLIN_GAME_STATE_HPP
#define GOBLIN_GAME_STATE_HPP

#include <boost/shared_ptr.hpp>
#include "gamestate.hpp"
#include "camera.hpp"
#include "living.hpp"

class GoblinGameState : public GameState
{
public:
	typedef boost::shared_ptr<GoblinGameState> ShPtr;
	
	std::list<Camera::ShPtr> cameras;
	TextCamera::ShPtr health_indicator;
	
	GoblinGameState(GameState::ShPtr p, Living::ShPtr e);
	virtual ~GoblinGameState() {}

	virtual void handle_input();
	virtual void draw();
};

#endif
