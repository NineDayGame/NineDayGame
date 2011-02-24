#ifndef PRINTABLE_HPP
#define PRINTABLE_HPP

#include <boost/shared_ptr.hpp>

class Printable
{
public:
	typedef boost::shared_ptr<Printable> ShPtr;
	
	virtual void print(const std::string output) = 0;
};

#endif
