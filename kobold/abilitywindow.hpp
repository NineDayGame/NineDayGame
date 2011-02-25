#ifndef NDG_ABILITYWINDOW_H_
#define NDG_ABILITYWINDOW_H_

#include <string>

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "font.hpp"
#include "glwindow.hpp"
#include "rect.hpp"
#include "printable.hpp"
//#include "util.hpp"

class AbilityWindow : public GlWindow {
public:
	typedef boost::shared_ptr<AbilityWindow> ShPtr;

	AbilityWindow();
	void init();
	void draw();
	
	void set_font(Font::ShPtr font);

	void set_ability(const std::string name, int index);

private:
	boost::shared_array<std::string> abilities_;
	Font::ShPtr font_;

	//DISALLOW_COPY_AND_ASSIGN(AbilityWindow);
};

#endif
