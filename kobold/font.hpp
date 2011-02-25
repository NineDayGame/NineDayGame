#ifndef NDG_FONT_H_
#define NDG_FONT_H_

#include <string>

#include <boost/shared_ptr.hpp>

#include "texture.hpp"
#include "util.hpp"

class Font {
public:
	typedef boost::shared_ptr<Font> ShPtr;

	Font(std::string name);
	
	// Returns the name of the font
	const std::string get_name() const;
	
	// Compares the name of this font with another name. Returns true if they're equal, false otherwise.
	const bool is_name(const std::string& rhs) const;
	
	// Returns the index of the display list associated with this font for rendering
	const int get_displaylist() const;
	
	// Sets the index of the display list for this font
	void set_displaylist(int index);
	
	// Returns the texture used by the font
	const Texture::ShPtr get_texture() const;
	
	// Sets the texture this font should use
	void set_texture(Texture::ShPtr tex);

private:
	std::string name_;
	int displaylist_;
	Texture::ShPtr texture_;

	DISALLOW_COPY_AND_ASSIGN(Font);
};

#endif
