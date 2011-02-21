#ifndef UTIL_HPP
#define UTIL_HPP

#include "camera.hpp"

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#define DCONVERT(to,from,var) boost::dynamic_pointer_cast<to,from>((var))
#define SCONVERT(to,from,var) boost::static_pointer_cast<to,from>((var))

extern TextCamera::ShPtr print_to;

void cprintf(const char* fmt, ...);

#endif
