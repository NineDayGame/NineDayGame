#ifndef NDG_HEALTHWINDOW_H_
#define NDG_HEALTHWINDOW_H_

#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "glwindow.hpp"
#include "rect.hpp"
#include "printable.hpp"
//#include "util.hpp"

class HealthWindow : public GlWindow {
public:
	typedef boost::shared_ptr<HealthWindow> ShPtr;

	HealthWindow();
	void init();
	void draw();
	void update_health(int current, int max);
	void set_dl_index(int dl_index);

private:
	std::string health_string_;
	int dl_index_;

	//DISALLOW_COPY_AND_ASSIGN(HealthWindow);
};

#endif
