#ifndef MENU_HPP
#define MENU_HPP

#include <libtcod.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include "camera.hpp"
#include "gamestate.hpp"
#include "menuitem.hpp"

class MenuItem;

class Menu : public GameState
{
public:
	typedef boost::shared_ptr<Menu> ShPtr;

	int screen_x;
	int screen_y;
	int width;
	int height;

	std::vector<boost::shared_ptr<MenuItem> > menu_items;
	int selected_index;

	Menu(GameState::ShPtr parent, int sx, int sy, int w, int h);
	virtual ~Menu();
	
	virtual void draw(TCODConsole* console);
	virtual void handle_key_press(TCOD_key_t key);
};

class InventoryMenu : public Menu
{
public:
	typedef boost::shared_ptr<InventoryMenu> ShPtr;

	InventoryMenu(GameState::ShPtr parent, int sx, int sy, int w, int h);
	virtual ~InventoryMenu();
	
	virtual void draw(TCODConsole* console);
	virtual void handle_key_press(TCOD_key_t key);
};

#endif
