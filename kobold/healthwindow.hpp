#ifndef NDG_HEALTHWINDOW_H_
#define NDG_HEALTHWINDOW_H_

#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "font.hpp"
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
	void set_font(Font::ShPtr font);

private:
	std::string health_string_;
	int dl_index_;
	Font::ShPtr font_;

	//DISALLOW_COPY_AND_ASSIGN(HealthWindow);
};

#endif
