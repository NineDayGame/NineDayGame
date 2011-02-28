#include <iostream>

#include "fontman.hpp"

FontMan::FontMan() 
  : loaded_(false) {
	init();
}

/*
 * This initialization function is just to make it easier to manually edit the 'to-be-loaded' font list.
 * In the future, FontMan should read from some kind of resource file so we don't need to specify these by
 * hand
 */
void FontMan::init() {
	font_names_.push_back(std::string("resources/terminal.png"));
}

/*
 * load_fonts iterates through each font in the font_names_ collection and attempts to load the font.
 * This implementation is guided mostly by NeHe Lesson 17:
 * http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=17
 * This method assumes a lot about the structure of the font texture being loaded. May need to update this
 * in the future. 
 */
void FontMan::load_fonts(TextureMan& texman) {
    if (loaded_) {
		std::cout << "FontMan: Error - fonts already loaded" << std::endl;
		return;
	}
    
    int font_count = font_names_.size();
    
    for (int j = 0; j < font_count; ++j) {
		const Texture::ShPtr fonttex = texman.get_texture(font_names_.at(j));
		
		if (fonttex) {
			float cx, cy;
			int dl_index = glGenLists( 256 );
			glBindTexture(GL_TEXTURE_2D, fonttex->get_index());

			for (int i = 0; i < 256; ++i) {

				cy = 1 - (float)(i % 16) / 16.0f;
				cx = 1 - (float)(i / 16) / 16.0f;

				glNewList(dl_index + (255 - i), GL_COMPILE);
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
			
			Font::ShPtr f (new Font(font_names_.at(j)));
			f->set_displaylist(dl_index);
			f->set_texture(fonttex);
			fonts_.push_back(f);
		}
	}
}

/*
 * Uses a dumb linear search to find a font with the same name. Optimizations welcome!
 */
const Font::ShPtr FontMan::get_font(std::string name) const {
	foreach (Font::ShPtr font, fonts_) {
		if (font->is_name(name)) {
			return font;
		}
	}
	
	return Font::ShPtr();
}
