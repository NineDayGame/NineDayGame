#include <libtcod.hpp>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "block.hpp"
#include "entity.hpp"
#include "living.hpp"
#include "glrenderer.hpp"
#include "map.hpp"
#include "vertex.hpp"

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

	for(int i = 0; i < 5; ++i)
	{
		int x,y;
		m->random_free_spot(&x,&y);
		Living::ShPtr e(new Living(Map::WkPtr(m),x,y,'0'+i,TCOD_red,1));
		m->add_entity(e);
	}

	Entity::ShPtr e = m->entities.front();
	
	if (argc==1) {		
		bool quit = false;

		GlRenderer::ShPtr glr (new GlRenderer());
		glr->load_map(m);
		
		float r = 0.0f;

		//Wait for user exit
		while( quit == false )
		{
			while ( SDL_PollEvent( &event ) ) {
				if ( event.type == SDL_QUIT ) {
					quit = true;
				}
			}
			
			glr->render();
		}

		clean_up();
	
	} else {

		TCODConsole::initRoot(width,height,"Test",false);

		while(!TCODConsole::isWindowClosed())
		{
			e->look();
			e->draw_map(TCODConsole::root);
			TCODConsole::flush();
			TCOD_key_t key=TCODConsole::waitForKeypress(true);
			if(key.vk == TCODK_ESCAPE) { break; }
			if(key.vk == TCODK_SPACE) { m->randomize(10); }
			
			if(key.vk == TCODK_KP8) { e->move(e->x,e->y-1); }
			if(key.vk == TCODK_KP2) { e->move(e->x,e->y+1); }
			if(key.vk == TCODK_KP4) { e->move(e->x-1,e->y); }
			if(key.vk == TCODK_KP6) { e->move(e->x+1,e->y); }
			if(key.vk == TCODK_KP7) { e->move(e->x-1,e->y-1); }
			if(key.vk == TCODK_KP9) { e->move(e->x+1,e->y-1); }
			if(key.vk == TCODK_KP1) { e->move(e->x-1,e->y+1); }
			if(key.vk == TCODK_KP3) { e->move(e->x+1,e->y+1); }
		}
	}

	return 0;
}
