#include <stdarg.h>
#include <stdio.h>
#include "util.hpp"

TextCamera::ShPtr print_to;

void cprintf(char const* format, ...)
{
	if(print_to)
	{
		char buffer[256];
		va_list args;
		va_start (args, format);
		vsprintf (buffer,format, args);
		va_end (args);
		
		print_to->print(buffer);
	}
}
