#include <iostream>

#include "SDL/SDL_image.h"

#include "textureman.hpp"

TextureMan::TextureMan() 
  : loaded_(false) {
	init();
}

/*
 * This initialization function is just to make it easier to manually edit the 'to-be-loaded' textures list.
 * In the future, TextureMan should read from some kind of resource file so we don't need to specify these by
 * hand
 */
void TextureMan::init() {
	tex_names_.push_back(std::string("resources/default.bmp"));
	tex_names_.push_back(std::string("resources/terminal.bmp"));
	tex_names_.push_back(std::string("resources/stone3.bmp"));
	tex_names_.push_back(std::string("resources/stonewall.png"));
}

/*
 * load_textures iterates through each texture in the tex_names_ collection and attempts to load the texture.
 * This implementation is guided mostly by NeHe Lesson 06:
 * http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=06
 */
void TextureMan::load_textures() {
	if (loaded_) {
		std::cout << "TextureMan: Error - textures already loaded" << std::endl;
		return;
	}
	
	unsigned int tex_count = tex_names_.size();
	unsigned int tex_indicies[tex_count];
	SDL_Surface *textureImage[tex_count];
	glGenTextures(tex_count, tex_indicies);

	for (int i = 0; i < tex_count; ++i) {
		//textureImage[i] = SDL_LoadBMP(tex_names_.at(i).c_str());
		textureImage[i] = IMG_Load(tex_names_.at(i).c_str());
		if (textureImage[i]) {		
			glBindTexture(GL_TEXTURE_2D, tex_indicies[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImage[i]->w, textureImage[i]->h, 0, GL_RGB,
					GL_UNSIGNED_BYTE, textureImage[i]->pixels );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			
			Texture::ShPtr tex (new Texture(tex_names_.at(i)));
			tex->set_index(tex_indicies[i]);
			textures_.push_back(tex);

			SDL_FreeSurface(textureImage[i]);
		} else {
			std::cout << "TextureMan: Error loading texture " << tex_names_.at(i) << std::endl;
		}
	}
	
	loaded_ = true;	
}

/*
 * Uses a dumb linear search to find a texture with the same name. Optimizations welcome!
 */
const Texture::ShPtr TextureMan::get_texture(std::string name) const {
	foreach (Texture::ShPtr tex, textures_) {
		if (tex->is_name(name)) {
			return tex;
		}
	}
	
	return Texture::ShPtr();
}
