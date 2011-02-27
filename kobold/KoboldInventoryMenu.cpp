#include "KoboldInventoryMenu.hpp"
#include "entity.hpp"
#include "item.hpp"
#include "util.hpp"
#include "kobold_gamestate.hpp"
#include "KoboldItemActionMenu.hpp"

static void create_action_menu(GameState::ShPtr m, MenuItem* me)
{
	Entity::ShPtr e = SCONVERT(Entity,void,me->args.at(0));
	Item::ShPtr i = SCONVERT(Item,void,me->args.at(1));
	KoboldInventoryMenu::ShPtr im = DCONVERT(KoboldInventoryMenu,GameState,m);
	KoboldItemActionMenu::ShPtr kiam(new KoboldItemActionMenu(im,im->player,im->screen_x+im->width,im->screen_y,100,im->height));
	kiam->init(e,i);
	kiam->set_font(im->font_);
	kiam->set_renderman(im->renderman_);
	GameState::state = kiam;
}

KoboldInventoryMenu::KoboldInventoryMenu(GameState::ShPtr parent, Living::ShPtr player, int sx, int sy, int w, int h)
	: KoboldMenu(parent,player,sx,sy,w,h)
{
	init();
}

KoboldInventoryMenu::~KoboldInventoryMenu() {}

void KoboldInventoryMenu::init()
{
	menu_window_.reset(new MenuWindow());
	menu_window_->set_position(screen_x, screen_y, 0);
	menu_window_->set_scale(width, height, 0);
	menu_window_->show();
	
	KoboldGameState::ShPtr m = SCONVERT(KoboldGameState,GameState,get_first_parent());
	Entity::ShPtr e = m->player;
	int i = 1;
	foreach(Container::ShPtr c, e->inventory)
	{
		Item::ShPtr item = SCONVERT(Item,Container,c);
		MenuItem::ShPtr mi(new MenuItem(screen_x+1,screen_y+i,item->name,TCOD_white,&create_action_menu));
		mi->args.push_back(e);
		mi->args.push_back(item);
		menu_items.push_back(mi);
		++i;
		menu_window_->push_item(mi->text);
	}
	if(menu_items.size() > 0)
	{
		menu_items.at(selected_)->select();
	}
	//parent->renderer->add_window(menu_window_);
}
