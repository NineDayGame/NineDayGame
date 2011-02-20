#include <libtcod.hpp>
#include <vector>

#include "map.hpp"
#include "block.hpp"
#include "vertex.hpp"
//The headers
#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

//Screen attributes
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 60;

//Event handler
SDL_Event event;

//The timer
class Timer
{
    private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

    public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

bool init_GL()
{
	glShadeModel(GL_SMOOTH);
    //Set clear color
    glClearColor( 0, 0, 0, 0 );
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

    //Set projection
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    //glOrtho( 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, -1, 1 );
	gluPerspective(45.0f,(GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT,1.0f,100.0f);

    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    
    glEnableClientState(GL_VERTEX_ARRAY);

    //If there was any errors
    if( glGetError() != GL_NO_ERROR )
    {
        return false;
    }

    //If everything initialized
    return true;
}

bool init()
{
    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        return false;
    }

    //Create Window
    if( SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL ) == NULL )
    {
        return false;
    }

    //Initialize OpenGL
    if( init_GL() == false )
    {
        return false;
    }

    //Set caption
    SDL_WM_SetCaption( "OpenGL Test", NULL );

    return true;
}

void clean_up()
{
    //Quit SDL
    SDL_Quit();
}

Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}

int main( int argc, char *argv[] )
{
    //Quit flag
    bool quit = false;

    //Initialize
    if( init() == false )
    {
        return 1;
    }

	std::vector<Movable::ShPtr> movables;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {
			Block::ShPtr blk (new Block());
			blk->set_position((float)i, (float)j, 0.0f);
			movables.push_back(blk);
		}
	}
	
	float r = 0.0f;

    //Our square object
    Block::ShPtr block (new Block());
	block->set_position(0.0f, 0.0f, -10.0f);

    //The frame rate regulator
    Timer fps;

	//Wait for user exit
	while( quit == false )
	{
        //Start the frame timer
        fps.start();

        //While there are events to handle
		while( SDL_PollEvent( &event ) )
		{
            //Handle key presses
            //square.handle_input();

			if( event.type == SDL_QUIT )
			{
                quit = true;
            }
		}

	    //Clear the screen
	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		glPolygonMode(GL_FRONT, GL_LINE);
		glPolygonMode(GL_BACK, GL_LINE);

		glTranslatef(0.0f, -3.0f, -15.0f);
		glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
		glRotatef(45.0f, -1.0f, 1.0f, 0.0f);

	    for (int i = 0; i < movables.size(); ++i) {
			movables.at(i)->draw();
		}
	    //Update screen
	    SDL_GL_SwapBuffers();

        //Cap the frame rate
        if( fps.get_ticks() < 1000 / FRAMES_PER_SECOND )
        {
            SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
        }
        glDisableClientState(GL_VERTEX_ARRAY);
	}

	//Clean up
	clean_up();

	return 0;
}

/*int main(int argc, char* argv[])
{
	TCODConsole::initRoot(80,50,"Test",false);

	Map m(80,50);
	m.clear();
	while(!TCODConsole::isWindowClosed())
	{
		m.draw(TCODConsole::root);
		TCODConsole::flush();
		TCOD_key_t key=TCODConsole::waitForKeypress(true);
		if(key.vk == TCODK_ESCAPE) { break; }
	}

	return 0;
}*/
