#ifndef NDG_MENUWINDOW_H_
#define NDG_MENUWINDOW_H_

#include <string>

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "font.hpp"
#include "gamestate.hpp"
#include "glwindow.hpp"
#include "menu.hpp"
#include "rect.hpp"
#include "printable.hpp"
//#include "util.hpp"

class MenuWindow : public GlWindow {
public:
	typedef boost::shared_ptr<MenuWindow> ShPtr;

	MenuWindow();
	virtual ~MenuWindow();
	virtual void init();
	virtual void draw();
	virtual void handle_input();
	
	void set_scale(float x, float y, float z);
	void clear_items();
	void push_item(const std::string name);
	void set_font(Font::ShPtr font);

private:
	GameState::ShPtr gamestate_;
	boost::shared_array<std::string> items_;
	Font::ShPtr font_;
	int item_max_;
	int tail_;

	//DISALLOW_COPY_AND_ASSIGN(MenuWindow);
};

#endif
