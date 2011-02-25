#ifndef INVENTORY_MENU_HPP
#define INVENTORY_MENU_HPP

#include "goblin_menu.hpp"

class InventoryMenu : public GoblinMenu
{
public:
	typedef boost::shared_ptr<InventoryMenu> ShPtr;

	InventoryMenu(GameState::ShPtr parent, int sx, int sy, int w, int h);
	virtual ~InventoryMenu();

	virtual void init();
};

#endif
