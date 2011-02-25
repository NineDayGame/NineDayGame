#include <iostream>

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
		textureImage[i] = SDL_LoadBMP(tex_names_.at(i).c_str());
		if (textureImage[i]) {		
			glBindTexture(GL_TEXTURE_2D, tex_indicies[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, 3, textureImage[i]->w, textureImage[i]->h, 0, GL_BGR,
					GL_UNSIGNED_BYTE, textureImage[i]->pixels );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			
			Texture::ShPtr tex (new Texture(tex_names_.at(i)));
			tex->set_index(tex_indicies[i]);
			textures_.push_back(tex);
			// TODO: Not sure if we can free this just yet - please check this
			//SDL_FreeSurface(textureImage[i]);
		} else {
			std::cout << "TextureMan: Error loading texture " << tex_names_.at(i) << std::endl;
		}
	}

	// TODO: Not sure if we have to do this down here... see above TODO
	for (int i = 0; i < tex_count; ++i) {
		if (textureImage[i]) {
			SDL_FreeSurface(textureImage[i]);
		}
	}
	
	loaded_ = true;	
}

/*
 * Uses a dumb linear search to find a texture with the same name. Optimizations welcome!
 */
const Texture::ShPtr TextureMan::get_texture(std::string name) const {
	std::cout << "Looking up texture " << name << std::endl;
	foreach (Texture::ShPtr tex, textures_) {
		std::cout << "Checking " << tex->get_name() << std::endl;
		if (tex->is_name(name)) {
			std::cout << "Match found " << tex->get_index() << std::endl;
			return tex;
		}
	}
	
	return Texture::ShPtr();
}
