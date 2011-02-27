#ifndef NDG_KOBOLDTARGETSTATE_HPP
#define NDG_KOBOLDTARGETSTATE_HPP

#include <libtcod.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include "gamestate.hpp"
#include "glcamera.hpp"
#include "item.hpp"
//#include "kobold_gamestate.hpp"
#include "renderman.hpp"

class KoboldTargetState : public GameState
{
public:
	typedef boost::shared_ptr<KoboldTargetState> ShPtr;

	KoboldTargetState(GameState::ShPtr parent, GlCamera::ShPtr camera, RenderMan::ShPtr renderman, int x, int y);
	virtual ~KoboldTargetState();

	virtual void init();
	
	virtual void draw();
	virtual void handle_input();
	void set_renderman(RenderMan::ShPtr renderman);
	
	RenderMan::ShPtr renderman_;
	
private:
	Movable::ShPtr reticule_;
	GlCamera::ShPtr camera_;
	int x_, y_;

};

#endif
