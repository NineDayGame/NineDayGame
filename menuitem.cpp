#include "menuitem.hpp"

MenuItem::MenuItem(int _x, int _y, std::string& _text, TCODColor _color, MenuItem::Operation _on_choose) : x(_x), y(_y), text(_text), color(_color), on_choose(_on_choose), selected(false)
{

}

MenuItem::~MenuItem()
{

}

void MenuItem::draw(TCODConsole* console)
{
	if(selected)
	{
		console->setBackgroundColor(TCOD_blue);
		console->printLeft(x,y,TCOD_BKGND_SET,text.c_str());
		console->setBackgroundColor(TCOD_black);
	}
	else
	{
		console->setBackgroundColor(TCOD_black);
		console->printLeft(x,y,TCOD_BKGND_SET,text.c_str());
	}
}

void MenuItem::select()
{
	selected = true;
}

void MenuItem::unselect()
{
	selected = false;
}

void MenuItem::choose(GameState::ShPtr parent)
{
	(*on_choose)(parent,this);
}
