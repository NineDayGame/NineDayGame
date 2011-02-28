#ifndef NDG_STAIRWAY_H_
#define NDG_STAIRWAY_H_

#include <boost/shared_ptr.hpp>

#include "util.hpp"
#include "movable.hpp"

class Stairway : public Movable {
public:
	typedef boost::shared_ptr<Stairway> ShPtr;

	Stairway();
	void init();

private:
	DISALLOW_COPY_AND_ASSIGN(Stairway);
};

#endif
