#ifndef NDG_KOBOLDINVENTORYMENU_HPP
#define NDG_KOBOLDINVENTORYMENU_HPP

#include "kobold_menu.hpp"

class KoboldInventoryMenu : public KoboldMenu
{
public:
	typedef boost::shared_ptr<KoboldInventoryMenu> ShPtr;

	KoboldInventoryMenu(GameState::ShPtr parent, Living::ShPtr player, int sx, int sy, int w, int h);
	virtual ~KoboldInventoryMenu();

	virtual void init();
};

#endif
