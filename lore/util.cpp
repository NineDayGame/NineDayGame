#include <stdarg.h>
#include <stdio.h>
#include "util.hpp"

TextCamera::ShPtr print_to_camera;
//GlConsoleWindow::ShPtr print_to_opengl;

void cprintf(char const* format, ...)
{
	char buffer[256];
	va_list args;
	va_start (args, format);
	vsprintf (buffer,format, args);
	va_end (args);
	if(print_to_camera)
	{		
		print_to_camera->print(buffer);
	}
	/*if(print_to_opengl)
	{
		print_to_opengl->print(buffer);
	}*/
	printf("%s\n",buffer);
}
