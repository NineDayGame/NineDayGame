#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "block.hpp"
#include "player.hpp"
#include "glrenderer.hpp"

//Screen attributes
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 60;

GlRenderer::GlRenderer() {
	init();
}

void GlRenderer::init() {
    
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        //error
    }

    if( SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL ) == NULL )
    {
        //error
    }

	init_gl();
    /*if( init_gl() == false )
    {
        //error
    }*/

    SDL_WM_SetCaption( "Nine Day Game", NULL );
    
    fps_.reset(new Timer());
}

void GlRenderer::init_gl() {
	glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(2.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT, 1.0f, 200.0f);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    if( glGetError() != GL_NO_ERROR )
    {
        //error
    }
    
    player_.reset(new Player());
}

void GlRenderer::load_map(const Map& map) {
	movables_.clear();
	for (int x = 0; x < map.width; ++x) {
		for (int y = 0; y < map.height; ++y) {
			if (map.display[x+y*map.width].c == '.') {
				Block::ShPtr blk (new Block());
				blk->set_position((float)x, (float)y, 0.0f);
				movables_.push_back(blk);
			} else if ((x > 0) && (y > 0)) { 
				if (map.display[x+y*map.width].c == '#'
			            && (map.display[(x-1)+y*map.width].c == '.'
			            || map.display[x+(y-1)*map.width].c == '.')) {
				
					for (int i = 0; i < 3; ++i) {
						Block::ShPtr blk (new Block());
						blk->set_position((float)x, (float)y, (float)i);
						movables_.push_back(blk);
					}
				}
			}
		}
	}
}

void GlRenderer::render() {
	fps_->start();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);

	glTranslatef(0.0f, -40.0f, -40.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(45.0f, -1.0f, 1.0f, 0.0f);

	for (int i = 0; i < movables_.size(); ++i) {
		movables_.at(i)->draw();
	}
	
	player_->draw();
	
	//Update screen
	SDL_GL_SwapBuffers();

	//Cap the frame rate
	if( fps_->get_ticks() < 1000 / FRAMES_PER_SECOND )
	{
		SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps_->get_ticks() );
	}
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void GlRenderer::update() {
}

void GlRenderer::set_player(float x, float y) {
	player_->set_position(x, y, 1.0f);
}

void GlRenderer::update_player(float x, float y) {
	player_->update_position(x, y);
}
