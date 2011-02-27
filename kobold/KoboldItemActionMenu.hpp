#ifndef NDG_KOBOLDITEMACTIONMENU_HPP
#define NDG_KOBOLDITEMACTIONMENU_HPP

#include "KoboldInventoryMenu.hpp"
#include "entity.hpp"
#include "item.hpp"

class KoboldItemActionMenu : public KoboldInventoryMenu
{
public:
	typedef boost::shared_ptr<KoboldItemActionMenu> ShPtr;

	KoboldItemActionMenu(GameState::ShPtr parent, Living::ShPtr player, int sx, int sy, int w, int h);
	virtual ~KoboldItemActionMenu();

	virtual void init(Entity::ShPtr e, Item::ShPtr i);
};

#endif
