#ifndef UTIL_HPP
#define UTIL_HPP

#include "printable.hpp"

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#define DCONVERT(to,from,var) boost::dynamic_pointer_cast<to,from>((var))
#define SCONVERT(to,from,var) boost::static_pointer_cast<to,from>((var))

void register_printable(Printable::ShPtr p);
void cprintf(const char* fmt, ...);

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
// Sourced from Google - see also: Effective C++ by Scott Meyers
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

#endif
