#ifndef NDG_FONTMAN_H_
#define NDG_FONTMAN_H_

#include <vector>

#include <boost/shared_ptr.hpp>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "font.hpp"
#include "textureman.hpp"
#include "util.hpp"

class FontMan {
public:
	typedef boost::shared_ptr<FontMan> ShPtr;

	FontMan();
	
	// Iterates through the list of textures that need to be loaded and loads them. First checks to see if
	// textures have been loaded to prevent duplicate loadings
	void load_fonts(TextureMan& texman);
	
	// Iterates through the list of loaded textures searching for a texture with the same name as "name".
	// Returns the first texture found with a matching name. Returns an empty pointer if no matching texture
	// is found.
	const Font::ShPtr get_font(const std::string name) const;

private:
	bool loaded_;
	std::vector<std::string> font_names_;
	std::vector<Font::ShPtr> fonts_;
	
	void init();
	
	DISALLOW_COPY_AND_ASSIGN(FontMan);
};

#endif
