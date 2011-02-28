#ifndef NDG_KILLCOUNTWINDOW_H_
#define NDG_KILLCOUNTWINDOW_H_

#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "font.hpp"
#include "glwindow.hpp"
#include "rect.hpp"
#include "printable.hpp"
//#include "util.hpp"

class KillCountWindow : public GlWindow {
public:
	typedef boost::shared_ptr<KillCountWindow> ShPtr;

	KillCountWindow();
	void init();
	void draw();
	void update_kills(int kills);
	void set_font(Font::ShPtr font);

private:
	std::string kill_string_;
	Font::ShPtr font_;

	//DISALLOW_COPY_AND_ASSIGN(KillCountWindow);
};

#endif
