#ifndef GOBLIN_TARGETSTATE_HPP
#define GOBLIN_TARGETSTATE_HPP

#include <boost/shared_ptr.hpp>
#include "gamestate.hpp"
#include "camera.hpp"
#include <string>
#include "living.hpp"

class GoblinTargetState : public GameState
{
public:
	typedef boost::shared_ptr<GoblinTargetState> ShPtr;

	typedef void (*TargetCallback)(Living::ShPtr e, std::string s, int x, int y);

	TargetCallback callback;

	std::string action;

	TargetingCamera::ShPtr camera;

	GoblinTargetState(GameState::ShPtr p, TargetingCamera::ShPtr c, Living::ShPtr e, std::string a, TargetCallback cb);
	virtual ~GoblinTargetState();

	virtual void handle_input();
	virtual void draw();
};

#endif
