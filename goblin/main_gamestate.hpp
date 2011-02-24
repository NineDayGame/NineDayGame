#ifndef MAIN_GAME_STATE_HPP
#define MAIN_GAME_STATE_HPP

#include <boost/shared_ptr.hpp>
#include "gamestate.hpp"
#include "camera.hpp"
#include "entity.hpp"

class MainGameState : public GameState
{
public:
	typedef boost::shared_ptr<MainGameState> ShPtr;
	
	Entity::ShPtr player;
	std::list<Camera::ShPtr> cameras;
	
	MainGameState(GameState::ShPtr p, Entity::ShPtr e);
	virtual ~MainGameState() {}

	virtual void handle_input();
	virtual void draw();
};

#endif
