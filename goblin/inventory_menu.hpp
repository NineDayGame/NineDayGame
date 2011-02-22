#ifndef INVENTORY_MENU_HPP
#define INVENTORY_MENU_HPP

#include "menu.hpp"

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
