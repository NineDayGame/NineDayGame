#include <stdarg.h>
#include <stdio.h>
#include "util.hpp"

TextCamera::ShPtr print_to;

void cprintf(char const* format, ...)
{
	char buffer[256];
	va_list args;
	va_start (args, format);
	vsprintf (buffer,format, args);
	va_end (args);
	if(print_to)
	{		
		print_to->print(buffer);
	}
	printf("%s\n",buffer);
}
