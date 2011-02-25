#ifndef NDG_TEXTUREMAN_H_
#define NDG_TEXTUREMAN_H_

#include <vector>

#include <boost/shared_ptr.hpp>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "texture.hpp"
#include "util.hpp"

class TextureMan {
public:
	typedef boost::shared_ptr<TextureMan> ShPtr;

	TextureMan();
	
	// Iterates through the list of textures that need to be loaded and loads them. First checks to see if
	// textures have been loaded to prevent duplicate loadings
	void load_textures();
	
	// Iterates through the list of loaded textures searching for a texture with the same name as "name".
	// Returns the first texture found with a matching name. Returns an empty pointer if no matching texture
	// is found.
	const Texture::ShPtr get_texture(const std::string name) const;

private:
	bool loaded_;
	std::vector<std::string> tex_names_;
	std::vector<Texture::ShPtr> textures_;
	
	void init();
	
	DISALLOW_COPY_AND_ASSIGN(TextureMan);
};

#endif
