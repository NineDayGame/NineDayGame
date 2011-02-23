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

	Menu(GameState::ShPtr parent, int sx, int sy, int w, int h);
	virtual ~Menu();

	virtual void init();
	
	virtual void draw(TCODConsole* console);
	virtual void handle_key_press(TCOD_key_t key);

};

#endif
