#ifndef NDG_MANAWINDOW_H_
#define NDG_MANAWINDOW_H_

#include <string>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "font.hpp"
#include "glwindow.hpp"
#include "rect.hpp"
#include "printable.hpp"
//#include "util.hpp"

class ManaWindow : public GlWindow {
public:
	typedef boost::shared_ptr<ManaWindow> ShPtr;

	ManaWindow();
	void init();
	void draw();
	void update_mana(int current, int max);
	void set_font(Font::ShPtr font);

private:
	std::string mana_string_;
	Font::ShPtr font_;

	//DISALLOW_COPY_AND_ASSIGN(ManaWindow);
};

#endif
