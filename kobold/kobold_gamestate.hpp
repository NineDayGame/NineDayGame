#ifndef KOBOLD_GAMESTATE_HPP
#define KOBOLD_GAMESTATE_HPP

#include <boost/shared_ptr.hpp>
#include "gamestate.hpp"
#include "entity.hpp"
#include "renderman.hpp"

class KoboldGameState : public GameState
{
public:
	typedef boost::shared_ptr<KoboldGameState> ShPtr;

	RenderMan::ShPtr renderer;
	Entity::ShPtr player;
	
	KoboldGameState(GameState::ShPtr p, RenderMan::ShPtr r, Entity::ShPtr e);
	virtual ~KoboldGameState() {}

	virtual void handle_input();
	virtual void draw();
};

#endif
