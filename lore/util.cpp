#include <stdarg.h>
#include <stdio.h>
#include <list>
#include <cmath>
#include "util.hpp"

std::list<Printable::ShPtr> util__printables;

void register_printable(Printable::ShPtr p)
{
	util__printables.push_back(p);
}

void cprintf(char const* format, ...)
{
	char buffer[256];
	va_list args;
	va_start (args, format);
	vsprintf (buffer,format, args);
	va_end (args);

	foreach(Printable::ShPtr p, util__printables)
	{
		p->print(buffer);
	}

	printf("%s\n",buffer);
}


double distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}
