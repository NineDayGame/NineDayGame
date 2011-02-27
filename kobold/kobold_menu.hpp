#ifndef NDG_KOBOLDMENU_HPP
#define NDG_KOBOLDMENU_HPP

#include <libtcod.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include "gamestate.hpp"
#include "item.hpp"
#include "menu.hpp"
#include "menuitem.hpp"
#include "menuwindow.hpp"
//#include "kobold_gamestate.hpp"
#include "font.hpp"
#include "renderman.hpp"

class KoboldMenu : public Menu
{
public:
	typedef boost::shared_ptr<KoboldMenu> ShPtr;

	KoboldMenu(GameState::ShPtr parent, Living::ShPtr player, int sx, int sy, int w, int h);
	virtual ~KoboldMenu();

	virtual void init();
	
	virtual void draw();
	virtual void handle_input();
	void set_font(Font::ShPtr font);
	void set_renderman(RenderMan::ShPtr renderman);
	
	RenderMan::ShPtr renderman_;
	Font::ShPtr font_;
	
	MenuWindow::ShPtr menu_window_;
	
protected:
	unsigned int selected_;

};

#endif
