#ifndef INVENTORY_MENU_HPP
#define INVENTORY_MENU_HPP

#include "goblin_menu.hpp"

class InventoryMenu : public GoblinMenu
{
public:
	typedef boost::shared_ptr<InventoryMenu> ShPtr;

	InventoryMenu(GameState::ShPtr parent, Living::ShPtr player, int sx, int sy, int w, int h);
	virtual ~InventoryMenu();

	virtual void init();
};

#endif
