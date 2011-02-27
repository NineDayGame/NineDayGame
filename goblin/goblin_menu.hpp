#ifndef GOBLINMENU_HPP
#define GOBLINMENU_HPP

#include <libtcod.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include "gamestate.hpp"
#include "menu.hpp"
#include "menuitem.hpp"

class GoblinMenu : public Menu
{
public:
	typedef boost::shared_ptr<GoblinMenu> ShPtr;

	/*int screen_x;
	int screen_y;
	int width;
	int height;

	std::vector<MenuItem::ShPtr> menu_items;
	int selected_index;

	int menu_offset;*/

	GoblinMenu(GameState::ShPtr parent, Living::ShPtr player, int sx, int sy, int w, int h);
	virtual ~GoblinMenu();

	virtual void init();
	
	virtual void draw();
	virtual void handle_input();

};

#endif
