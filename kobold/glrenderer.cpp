#include <stdlib.h>
#include <iostream>
#include <libtcod.hpp>
#include <math.h>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "block.hpp"
#include "player.hpp"
#include "glrenderer.hpp"

//Screen attributes
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 600;
const int SCREEN_BPP = 32;

//The frame rate
const int FRAMES_PER_SECOND = 60;

GlRenderer::GlRenderer()
  : lights_(true), wireframes_(false) {
	init();
}

void GlRenderer::init() {
    
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        //error
    }

	sdlSurface_ = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL );
    /*if( SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL ) == NULL )
    {
        //error
    }*/

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
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //GLfloat ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT, 1.0f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if( glGetError() != GL_NO_ERROR )
    {
        //error
    }
}

void GlRenderer::set_camera(GlCamera::ShPtr camera) {
	camera_ = camera;
}

void GlRenderer::set_dynamic_light(Light::ShPtr light) {
	dynamic_light_ = light;
}

int GlRenderer::add_window(const GlWindow::ShPtr window) {
	windows_.push_back(window);
	return windows_.size() - 1;
}

void GlRenderer::add_movable(const Movable::ShPtr movable) {
	movables_.push_back(movable);
}

void GlRenderer::clear_windows() {
	windows_.clear();
}

void GlRenderer::clear_movables() {
	movables_.clear();
}

void GlRenderer::remove_window(GlWindow::ShPtr window) {
	windows_.remove(window);
}

void GlRenderer::load_terrain(Movable::ShPtr movable) {
	terrain_.push_back(movable);
}

void GlRenderer::clear_terrain() {
	terrain_.clear();
}

void GlRenderer::render() {
	fps_->start();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY_EXT);

	camera_->setup_camera();

	Movable::ShPtr mov;

	for (int i = 0; i < terrain_.size(); ++i) {
		mov = terrain_.at(i);
		float distance = mov->get_position()->distance(*(dynamic_light_->get_position()));
		// Do some range culling
		if (distance < 30.0f) {
			if (distance <= dynamic_light_->get_radius()+1) {
				set_light(GL_LIGHT0, *dynamic_light_);
			} else {
				Light none; 
				set_light(GL_LIGHT0, none);
			}
			terrain_.at(i)->draw();
		}
	}
	
	for (int i = 0; i < movables_.size(); ++i) {
		mov = movables_.at(i);
		if (mov->get_position()->distance(*(dynamic_light_->get_position())) <= dynamic_light_->get_radius()+1) {
			set_light(GL_LIGHT0, *dynamic_light_);
		} else {
			Light none; 
			set_light(GL_LIGHT0, none);
		}
		movables_.at(i)->draw();
	}
	
	//player_->draw();
	
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	
	foreach(GlWindow::ShPtr window, windows_) {
		window->draw();
	}
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glEnable(GL_LIGHTING);

	SDL_GL_SwapBuffers();

	//Cap the frame rate
	if( fps_->get_ticks() < 1000 / FRAMES_PER_SECOND )
	{
		SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps_->get_ticks() );
	}
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void GlRenderer::set_ambient_light(const Vector4f& light) {
	GLfloat ambient[] = {light.w, light.x, light.y, light.z};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
}

void GlRenderer::set_light(int index, const Light& light) {
	
	Vector4f::ShPtr v4f = light.get_ambient();
	GLfloat lightVals[4] = {v4f->w, v4f->x, v4f->y, v4f->z};
	glLightfv(index, GL_AMBIENT, lightVals);
    
    v4f = light.get_diffuse();
    lightVals[0] = v4f->w;
    lightVals[1] = v4f->x;
    lightVals[2] = v4f->y;
    lightVals[3] = v4f->z;
    glLightfv(index, GL_DIFFUSE, lightVals);
    
    v4f = light.get_specular();
    lightVals[0] = v4f->w;
    lightVals[1] = v4f->x;
    lightVals[2] = v4f->y;
    lightVals[3] = v4f->z;
    glLightfv(index, GL_SPECULAR, lightVals);

    const Vector3f::ShPtr v3f = light.get_position();
    lightVals[0] = v3f->x;
    lightVals[1] = v3f->y;
    lightVals[2] = v3f->z;
    lightVals[3] = 1.0f;
    glLightfv(index, GL_POSITION, lightVals);
    //std::cout << "Setting light pos: " << lightVals[0] << ", " << lightVals[1] << ", " << lightVals[2];
    
    glLightf(index, GL_CONSTANT_ATTENUATION, light.get_attenuation_constant());
    glLightf(index, GL_LINEAR_ATTENUATION, light.get_attenuation_linear());
	glLightf(index, GL_QUADRATIC_ATTENUATION, light.get_attenuation_quadratic());
}

void GlRenderer::take_screenshot(std::string filename) {

	SDL_Surface *temp;
	unsigned char *pixels;
	int i;
	
	if (!(sdlSurface_->flags & SDL_OPENGL)) {
			SDL_SaveBMP(temp, filename.c_str());
			return;
	}
			
	temp = SDL_CreateRGBSurface(SDL_SWSURFACE, sdlSurface_->w, sdlSurface_->h, 24,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	0x000000FF, 0x0000FF00, 0x00FF0000, 0
#else
	0x00FF0000, 0x0000FF00, 0x000000FF, 0
#endif
	);
	if (temp == NULL) { return; }

	pixels = (unsigned char *)malloc(3 * sdlSurface_->w * sdlSurface_->h);
	if (pixels == NULL) {
		SDL_FreeSurface(temp);
		return;
	}

	glReadPixels(0, 0, sdlSurface_->w, sdlSurface_->h, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	for (i=0; i<sdlSurface_->h; i++) {
		memcpy(((char *) temp->pixels) + temp->pitch * i, pixels + 3*sdlSurface_->w * (sdlSurface_->h-i-1),
			   sdlSurface_->w*3);
	}
	
	free(pixels);

	SDL_SaveBMP(temp, filename.c_str());
	SDL_FreeSurface(temp);
}

void GlRenderer::toggle_fullscreen() {
	SDL_WM_ToggleFullScreen( sdlSurface_ );
}

void GlRenderer::toggle_lighting() {
	if (lights_) {
		glDisable(GL_LIGHTING);
	} else {
		glEnable(GL_LIGHTING);
	}
	lights_ = !lights_;
}

void GlRenderer::toggle_wireframes() {
	if (wireframes_) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	} else {
		//glPolygonMode(GL_FRONT, GL_POINT);
		//glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	wireframes_ = !wireframes_;
}
