#ifndef NDG_GLCONSOLEWINDOW_H_
#define NDG_GLCONSOLEWINDOW_H_

#include <string>

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "glwindow.hpp"
#include "rect.hpp"
#include "printable.hpp"
//#include "util.hpp"

class GlConsoleWindow : public GlWindow, public Printable {
public:
	typedef boost::shared_ptr<GlConsoleWindow> ShPtr;

	GlConsoleWindow();
	void init();
	void draw();
	
	void set_dl_index(int dl_index);

	virtual void print(const std::string s);

private:
	boost::shared_array<std::string> console_;
	int top_;
	int dl_index_;

	//DISALLOW_COPY_AND_ASSIGN(GlConsoleWindow);
};

#endif
