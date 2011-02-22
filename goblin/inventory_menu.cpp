#include "inventory_menu.hpp"
#include "entity.hpp"
#include "item.hpp"
#include "util.hpp"
#include "main_gamestate.hpp"

static void foo(GameState::ShPtr m, MenuItem* me)
{
	Item::ShPtr i = SCONVERT(Item,void,me->args.at(0));
	cprintf("The %s is %s.",i->name.c_str(),i->description.c_str());
}

InventoryMenu::InventoryMenu(GameState::ShPtr parent, int sx, int sy, int w, int h) : Menu(parent,sx,sy,w,h)
{
	MainGameState::ShPtr m = SCONVERT(MainGameState,GameState,parent);
	Entity::ShPtr e = m->player;
	int i = 1;
	foreach(Container::ShPtr c, e->inventory)
	{
		Item::ShPtr item = SCONVERT(Item,Container,c);
		MenuItem::ShPtr mi(new MenuItem(screen_x+1,screen_y+i,item->name,TCOD_white,&foo));
		mi->args.push_back(item);
		menu_items.push_back(mi);
		++i;
	}
	menu_items.at(selected_index)->select();
}
InventoryMenu::~InventoryMenu() {}
	
void InventoryMenu::draw(TCODConsole* console)
{
	Menu::draw(console);
	foreach(MenuItem::ShPtr mi, menu_items)
	{
		mi->draw(console);
	}
	
}
void InventoryMenu::handle_key_press(TCOD_key_t key)
{
	Menu::handle_key_press(key);
	if(key.vk == TCODK_ENTER)
	{
		foreach(MenuItem::ShPtr mi, menu_items)
		{
			if(mi->selected) { mi->choose(this->shared_from_this()); break; }
		}
	}
	if(key.vk == TCODK_UP)
	{
		menu_items.at(selected_index)->unselect();
		selected_index = (selected_index-1)%menu_items.size();
		menu_items.at(selected_index)->select();
	}
	if(key.vk == TCODK_DOWN)
	{
		menu_items.at(selected_index)->unselect();
		selected_index = (selected_index+1)%menu_items.size();
		menu_items.at(selected_index)->select();
	}
}
