#ifndef MENUITEM_HPP
#define MENUITEM_HPP

#include <boost/shared_ptr.hpp>
#include <libtcod.hpp>
#include <string>
#include "gamestate.hpp"

class MenuItem
{
public:
	typedef boost::shared_ptr<MenuItem> ShPtr;
	typedef void (*Operation)(GameState::ShPtr, MenuItem*);
	
	int x;
	int y;
	std::string text;
	TCODColor color;
	bool selected;
	
	MenuItem::Operation on_choose;

	MenuItem(int x, int y, std::string& text, TCODColor color, MenuItem::Operation on_choose);
	virtual ~MenuItem();

	virtual void draw(TCODConsole* console);
	virtual void select();
	virtual void unselect();

	virtual void choose(GameState::ShPtr parent);
};

#endif
