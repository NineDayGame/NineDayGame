#ifndef MENU_HPP
#define MENU_HPP

#include <libtcod.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include "gamestate.hpp"
#include "menuitem.hpp"

class Menu : public GameState
{
public:
	typedef boost::shared_ptr<Menu> ShPtr;

	int screen_x;
	int screen_y;
	int width;
	int height;

	std::vector<MenuItem::ShPtr> menu_items;
	int selected_index;

	int menu_offset;

	Menu(GameState::ShPtr p, Living::ShPtr player, int sx, int sy, int w, int h)
		: GameState(p,player),
	    screen_x(sx), screen_y(sy),
	    width(w), height(h),
	    selected_index(0),
	    menu_offset(0) { }
	
	virtual ~Menu() {}

	virtual void init() = 0;
	
	virtual void draw() = 0;
	virtual void handle_input() = 0;

};

#endif
