#ifndef ACTION_MENU_HPP
#define ACTION_MENU_HPP

#include "goblin_menu.hpp"

class ActionMenu : public GoblinMenu
{
public:
	typedef boost::shared_ptr<ActionMenu> ShPtr;

	ActionMenu(GameState::ShPtr parent, Living::ShPtr player, int sx, int sy, int w, int h);
	virtual ~ActionMenu();

	virtual void init();
};


#endif
