#include <libtcod.hpp>
#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "block.hpp"
#include "glrenderer.hpp"
#include "map.hpp"
#include "vertex.hpp"

//Event handler
SDL_Event event;

void clean_up()
{
    //Quit SDL
    SDL_Quit();
}

int main( int argc, char *argv[] )
{
    //Quit flag
    bool quit = false;

	GlRenderer::ShPtr glr (new GlRenderer());
	
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

	return 0;
}
