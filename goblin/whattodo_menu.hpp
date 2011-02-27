#ifndef WHATTODO_MENU_HPP
#define WHATTODO_MENU_HPP

#include "inventory_menu.hpp"
#include "entity.hpp"
#include "item.hpp"

class WhatToDoMenu : public InventoryMenu
{
public:
	typedef boost::shared_ptr<WhatToDoMenu> ShPtr;

	WhatToDoMenu(GameState::ShPtr parent, Living::ShPtr player, int sx, int sy, int w, int h);
	virtual ~WhatToDoMenu();

	virtual void init(Entity::ShPtr e, Item::ShPtr i);
};

#endif
