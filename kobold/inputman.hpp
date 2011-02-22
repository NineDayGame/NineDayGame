#ifndef NDG_INPUTMAN_H_
#define NDG_INPUTMAN_H_

#include <boost/shared_ptr.hpp>

#include "entity.hpp"
#include "renderman.hpp"
#include "util.hpp"

class InputMan {
public:
	typedef boost::shared_ptr<InputMan> ShPtr;

	InputMan();
	void set_entity(Entity::ShPtr entity);
	void set_renderman(RenderMan::ShPtr rman);
	bool read_input();

private:
	RenderMan::ShPtr renderman_;
	Entity::ShPtr e_;
	SDL_Event event_;
	
	DISALLOW_COPY_AND_ASSIGN(InputMan);
};

#endif
