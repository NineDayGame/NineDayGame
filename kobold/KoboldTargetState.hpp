#ifndef NDG_KOBOLDTARGETSTATE_HPP
#define NDG_KOBOLDTARGETSTATE_HPP

#include <vector>
#include <string>

#include <libtcod.hpp>
#include <boost/shared_ptr.hpp>

#include "gamestate.hpp"
#include "glcamera.hpp"
//#include "kobold_gamestate.hpp"
#include "renderman.hpp"

// ---------------
// TODO: Included for the TargetCallback typedef
#include "goblin_targetstate.hpp"
// ---------------

class KoboldTargetState : public GameState
{
public:
	typedef boost::shared_ptr<KoboldTargetState> ShPtr;

	KoboldTargetState(GameState::ShPtr parent, Living::ShPtr player, GlCamera::ShPtr camera, RenderMan::ShPtr renderman, GoblinTargetState::TargetCallback callback, int x, int y);
	virtual ~KoboldTargetState();

	virtual void init();
	
	virtual void draw();
	virtual void handle_input();
	void set_renderman(RenderMan::ShPtr renderman);
	
	GoblinTargetState::TargetCallback callback_;
	
	RenderMan::ShPtr renderman_;
	
private:
	Movable::ShPtr reticule_;
	GlCamera::ShPtr camera_;
	int x_, y_;

};

#endif
