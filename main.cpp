#include <libtcod.hpp>
#include <list>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "block.hpp"
#include "entity.hpp"
#include "living.hpp"
#include "glrenderer.hpp"
#include "map.hpp"
#include "vector3f.hpp"
#include "camera.hpp"
#include "item.hpp"
#include "menu.hpp"
#include "util.hpp"
#include <boost/lexical_cast.hpp>

#include "main_gamestate.hpp"

//Event handler
SDL_Event event;

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

	TCODRandom* rand = TCODRandom::getInstance();
	for(int i = 0; i < 50; ++i)
	{
		char buf[32];
		int x,y;
		m->random_free_spot(&x,&y);
		sprintf(buf,"Entity %d",i);

		TCODColor color(rand->getInt(0,255),rand->getInt(0,255),rand->getInt(0,255));
		Living::ShPtr e(new Living(Map::WkPtr(m),buf,x,y,'0'+i,color,3));
		m->get(e);
	}

	for(int i = 0; i < 50; ++i)
	{
		char name[32];
		char desc[32];
		int x,y;
		m->random_free_spot(&x,&y);
		sprintf(name,"Item %d",i);
		sprintf(desc,"A shiny item.");

		//TCODColor color(rand->getInt(0,255),rand->getInt(0,255),rand->getInt(0,255));
		Item::ShPtr e(new Item(Map::WkPtr(m),name,desc,x,y,'I',TCOD_green));
		m->get(e);
	}

	Entity::ShPtr e = SCONVERT(Entity,Container,m->inventory.front());
	
	if (argc==1) {		
		int ssc = 0;
		bool quit = false;

		GlRenderer::ShPtr glr (new GlRenderer());
		//glr->load_map(*(e->known_map));
		e->look();

		while( quit == false )
		{
			while ( SDL_PollEvent( &event ) ) {
				if( event.type == SDL_KEYDOWN ) {
					switch( event.key.keysym.sym )
					{
						case SDLK_UP: e->move(e->x, e->y+1); e->look(); break;
						case SDLK_DOWN: e->move(e->x, e->y-1); e->look(); break;
						case SDLK_LEFT: e->move(e->x-1, e->y); e->look(); break;
						case SDLK_RIGHT: e->move(e->x+1, e->y); e->look(); break;
						case SDLK_F1: glr->enable_fullscreen(); break;
						case SDLK_F2: glr->toggle_lighting(); break;
						case SDLK_F3: glr->toggle_wireframes(); break;
						case SDLK_F12: glr->take_screenshot(std::string("screenshot.bmp")); break;
						/*case SDLK_UP: glr->set_player(0.0f, 1.0f); break;
						case SDLK_DOWN: glr->set_player(0.0f, -1.0f); break;
						case SDLK_LEFT: glr->set_player(1.0f, 0.0f); break;
						case SDLK_RIGHT: glr->set_player(-1.0f, 0.0f); break;*/
					}
					/*std::string filename = std::string("screenshot");
					if (ssc < 100) {
						filename += "0";
					} else if (ssc < 10) {
						filename += "00";
					}
					filename += boost::lexical_cast<std::string>(ssc++);
					filename += ".bmp";
					glr->take_screenshot(filename);*/
				}
				
				if ( event.type == SDL_QUIT ) {
					quit = true;
				}
			}
			
			//glr->load_map(*m);
			glr->load_map(*(e->known_map));
			glr->load_mobs(e->seen);
			glr->set_player((float)e->x, (float)e->y);
			glr->render();
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
		print_to = tc;

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
