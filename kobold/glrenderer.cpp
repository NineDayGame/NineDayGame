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
  : cameraX_(0.0f), cameraY_(0.0f), cameraZ_(-60.0f),
    lightX_(0.0f), lightY_(0.0f), lightZ_(0.0f),
    lights_(true), wireframes_(false) {
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

	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //GLfloat ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat ambient[] = {0.05f, 0.05f, 0.05f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluPerspective(45.0f, (GLfloat)SCREEN_WIDTH/(GLfloat)SCREEN_HEIGHT, 1.0f, 200.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if( glGetError() != GL_NO_ERROR )
    {
        //error
    }
    
    load_textures();
    load_font();
    player_.reset(new Player());
    player_->set_texture(texture[0]);
    Light::ShPtr plight = player_->get_light();
    Vector4f::ShPtr amb (new Vector4f(0.08f, 0.08f, 0.08f, 1.0f));
    plight->set_ambient(amb);
    Vector4f::ShPtr diff (new Vector4f(1.0f, 0.9f, 0.7f, 1.0f));
    plight->set_diffuse(diff);
    plight->set_attenuation_constant(0.5f);
    plight->set_attenuation_linear(0.01f);
    plight->set_attenuation_quadratic(0.01f);

	cwindow_.reset(new GlConsoleWindow());
	cwindow_->set_dl_index(dl_index_);
	cwindow_->set_texture(texture[2]);
	cwindow_->show();
	cwindow_->print(std::string("Welcome to NineDayGame"));
	//print_to_opengl = cwindow_;
	sheet_window_.reset(new GlWindow());
	inventory_window_.reset(new GlWindow());
}

void GlRenderer::load_map(const Map& map) {
	
	movables_.clear();
	for (int x = 0; x < map.width; ++x) {
		for (int y = 0; y < map.height; ++y) {
			if (map.display[x+y*map.width].c == '.') {
				Block::ShPtr blk (new Block());
				blk->set_position((float)x, (float)y, 0.0f);
				blk->set_texture(texture[1]);
				TCODColor c = map.display[x+y*map.width].color;
				blk->set_color(Vector3f((c.r/255.0f), (c.g/255.0f), (c.b/255.0f)));
				movables_.push_back(blk);
			} else if ((x > 0) && (y > 0)) { 
				if (map.display[x+y*map.width].c == '#'
			            && (map.display[(x-1)+y*map.width].c == '.'
			            || map.display[x+(y-1)*map.width].c == '.')) {
				
					for (int i = 0; i < 3; ++i) {
						Block::ShPtr blk (new Block());
						blk->set_position((float)x, (float)y, (float)i);
						if (i < 2) {
							TCODColor c = map.display[x+y*map.width].color;
							//blk->set_texture(texture[0]);
							blk->set_color(Vector3f((c.r/255.0f), (c.g/255.0f), (c.b/255.0f)));
						}
						movables_.push_back(blk);
					}
				}
			}
		}
	}
}

void GlRenderer::load_mobs(std::list<Entity::WkPtr> mobs) {
	//for (int i = 0; i < mobs.size(); ++i) {
	foreach (Entity::WkPtr e, mobs) {
		Character::ShPtr chr (new Character());
		Entity::ShPtr m = e.lock();
		if(m)
		{
			chr->set_position(m->x, m->y, 0.5f);
			TCODColor c = m->color;
			chr->set_texture(texture[0]);
			chr->set_color(Vector3f((c.r/255.0f), (c.g/255.0f), (c.b/255.0f)));
			movables_.push_back(chr);
		}
	}
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

	glTranslatef(cameraX_, cameraY_, cameraZ_);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(45.0f, -1.0f, 1.0f, 0.0f);

	for (int i = 0; i < movables_.size(); ++i) {
		if (movables_.at(i)->get_position()->distance(*(player_->get_position())) <= player_->get_sight_radius()+1) {
			set_light(GL_LIGHT0, *(player_->get_light()));
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
	
	cwindow_->draw();
	//printgl(0, 0, std::string("Hero explodes into tiny bits of goo!"));
	
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	//glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();
	//glPopMatrix();
	//glMatrixMode(GL_MODELVIEW);
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

void GlRenderer::load_textures() {

	texture.reset(new unsigned int[3]);
	SDL_Surface *textureImage[3]; 

	//if ((textureImage[0] = SDL_LoadBMP( "default.bmp" ))) {
		textureImage[0] = SDL_LoadBMP("resources/default.bmp");
		textureImage[1] = SDL_LoadBMP("resources/stone3.bmp");
		textureImage[2] = SDL_LoadBMP("resources/terminal.bmp");
		
		glGenTextures( 3, &texture[0] );
		
		glBindTexture( GL_TEXTURE_2D, texture[0] );
		glTexImage2D( GL_TEXTURE_2D, 0, 3, textureImage[0]->w, textureImage[0]->h, 0, GL_BGR,
		        GL_UNSIGNED_BYTE, textureImage[0]->pixels );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		
		glBindTexture( GL_TEXTURE_2D, texture[1] );
		glTexImage2D( GL_TEXTURE_2D, 0, 3, textureImage[1]->w, textureImage[1]->h, 0, GL_BGR,
		        GL_UNSIGNED_BYTE, textureImage[1]->pixels );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		
		glBindTexture( GL_TEXTURE_2D, texture[2] );
		glTexImage2D( GL_TEXTURE_2D, 0, 3, textureImage[2]->w, textureImage[2]->h, 0, GL_BGR,
		        GL_UNSIGNED_BYTE, textureImage[2]->pixels );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	//}

    if (textureImage[0]) {
	    SDL_FreeSurface(textureImage[0]);
	}
	if (textureImage[1]) {
	    SDL_FreeSurface(textureImage[1]);
	}
	if (textureImage[2]) {
	    SDL_FreeSurface(textureImage[2]);
	}
}

void GlRenderer::load_font() {
    float cx, cy;
    dl_index_ = glGenLists( 256 );
    glBindTexture(GL_TEXTURE_2D, texture[2]);

    for (int i = 0; i < 256; ++i) {

	    cy = 1 - (float)(i % 16) / 16.0f;
	    cx = 1 - (float)(i / 16) / 16.0f;

	    glNewList(dl_index_ + (255 - i), GL_COMPILE);
		glBegin(GL_QUADS);
		glTexCoord2f(cx - 0.0625, cy);
		glVertex2i(0, 0);

		glTexCoord2f(cx, cy);
		glVertex2i(8, 0);

		glTexCoord2f(cx, cy - 0.0625f);
		glVertex2i(8, 8);

		glTexCoord2f(cx - 0.0625f, cy - 0.0625f);
		glVertex2i(0, 8);
		glEnd();

		glTranslated(8, 0, 0);
	    glEndList();
	}
}

void GlRenderer::printgl(std::string output)
{
	/*glPushMatrix();
    glLoadIdentity();
    glTranslated(x, y, 0);
    glListBase(dl_index_ - 0);
    glBindTexture( GL_TEXTURE_2D, texture[2] );
    glCallLists(output.size(), GL_BYTE, output.c_str());
	glPopMatrix();*/
	cwindow_->print(output);
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

void GlRenderer::set_sight_radius(float r) {
	player_->set_sight_radius(r);
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

void GlRenderer::update() {
}

void GlRenderer::set_player(float x, float y) {

	cameraX_ = -0.7071f*x + 0.7071f*y;
	cameraY_ = -0.5f*x + -0.5f*y;
	cameraZ_ = -30.0f + 0.5*x + 0.5f*y;
	
	lightX_ = x;
	lightY_ = y;
	lightZ_ = 2.0f;
	
	player_->set_position(x, y, 1.0f);
}
