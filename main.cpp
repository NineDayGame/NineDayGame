#include <libtcod.hpp>
#include <list>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "block.hpp"
#include "entity.hpp"
#include "living.hpp"
#include "glrenderer.hpp"
#include "map.hpp"
#include "vertex.hpp"
#include "camera.hpp"

#include "util.hpp"

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

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

	for(int i = 0; i < 50; ++i)
	{
		char buf[32];
		int x,y;
		m->random_free_spot(&x,&y);
		sprintf(buf,"Entity %d",i);
		Living::ShPtr e(new Living(Map::WkPtr(m),buf,x,y,'0'+i,TCOD_red,3));
		m->add_entity(e);
	}

	Entity::ShPtr e = m->entities.front();
	Entity::ShPtr e2 = m->entities.back();
	
	if (argc==1) {		
		bool quit = false;

		GlRenderer::ShPtr glr (new GlRenderer());
		//glr->load_map(*(e->known_map));
		
		float r = 0.0f;

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
					}
				}
				
				if ( event.type == SDL_QUIT ) {
					quit = true;
				}
			}
			
			glr->load_map(*(e->known_map));
			//glr->load_map(*m);
			glr->set_player((float)e->x, (float)e->y);
			glr->render();
		}

		clean_up();
	
	} else {

		TCODConsole::initRoot(width,height,"Test",false);

		std::list<Camera::ShPtr> cameras;
		Camera::ShPtr c;
		c = EntityCamera::ShPtr(new EntityCamera(e->known_map,e,0,20,100,80));
		cameras.push_back(c);
		c = TextCamera::ShPtr(new TextCamera(0,0,100,20));
		cameras.push_back(c);

		TextCamera::ShPtr tc = boost::static_pointer_cast<TextCamera,Camera>(c);
		print_to = tc;

		while(!TCODConsole::isWindowClosed())
		{
			foreach(Camera::ShPtr c, cameras)
			{
				c->draw(TCODConsole::root);
			}

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
