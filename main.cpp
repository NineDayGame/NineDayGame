#include <libtcod.hpp>
#include <list>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "block.hpp"
#include "entity.hpp"
#include "living.hpp"
#include "map.hpp"
#include "vector3f.hpp"
#include "camera.hpp"
#include "item.hpp"
#include "menu.hpp"
#include "util.hpp"
#include "renderman.hpp"
#include "inputman.hpp"
#include "monster.hpp"

#include "main_gamestate.hpp"

void clean_up()
{
    SDL_Quit();
}

int main(int argc, char* argv[])
{
	int width = 120;
	int height = 80;

	Map::ShPtr m(new Map(width,height));
	m->clear();
	m->randomize(10);

	int x,y;
	m->random_free_spot(&x,&y);
	Living::ShPtr l(new Living(Map::WkPtr(m),"Hero",x,y,'@',TCOD_red,30));
	m->get(l);

	TCODRandom* rand = TCODRandom::getInstance();
	for(int i = 0; i < 50; ++i)
	{
		char buf[32];
		char name[32];
		char desc[32];
		int x,y;
		m->random_free_spot(&x,&y);
		sprintf(buf,"Entity %d",i);
		sprintf(name,"Item %d",i);
		sprintf(desc,"A shiny item.");

		TCODColor color(rand->getInt(0,255),rand->getInt(0,255),rand->getInt(0,255));
		Monster::ShPtr e(new Monster(Map::WkPtr(m),buf,x,y,'0'+i,color,3));
		Item::ShPtr i(new Item(Map::WkPtr(m),name,desc,x,y,'I',TCOD_green));
		e->get(i);
		m->get(e);
	}
	Entity::ShPtr e = SCONVERT(Entity,Container,m->inventory.front());
	
	if (argc==1) {		
		bool quit = false;

		RenderMan::ShPtr renderman (new RenderMan());
		renderman->set_entity(e);
		InputMan::ShPtr inputman (new InputMan());
		inputman->set_renderman(renderman);
		inputman->set_entity(e);

		while( quit == false )
		{
			quit = inputman->read_input();
			renderman->draw_frame();
		}

		clean_up();
	
	} else {

		TCODConsole::initRoot(width,height,"Test",false);

		std::list<Container::ShPtr>::iterator i = m->inventory.begin();
		std::list<Entity::ShPtr> follow;
		for(int j = 0; j < 0; ++j)
		{
			follow.push_back(SCONVERT(Entity,Container,*(++i)));
		}
		follow.push_front(e);

		MainGameState::ShPtr mgs(new MainGameState(GameState::ShPtr(),e));
		GameState::state = mgs;
		
		Camera::ShPtr c;
		int q = 0;
		foreach(Entity::ShPtr e, follow)
		{
			int size = width/follow.size();
			c = EntityCamera::ShPtr(new EntityCamera(e->known_map,e,q*size,20,size,60));
			mgs->cameras.push_back(c);
			++q;
		}

		c = TextCamera::ShPtr(new TextCamera(0,0,width,20));
		mgs->cameras.push_back(c);
		TextCamera::ShPtr tc = SCONVERT(TextCamera,Camera,c);
		print_to_camera = tc;

		while(!TCODConsole::isWindowClosed())
		{
			GameState::state->draw(TCODConsole::root);

			//TCODSystem::saveScreenshot(NULL);
			TCODConsole::flush();
			TCOD_key_t key=TCODConsole::waitForKeypress(true);
			GameState::state->handle_key_press(key);
		}
	}

	return 0;
}
