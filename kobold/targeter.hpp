#ifndef NDG_TARGETER_H_
#define NDG_TARGETER_H_

#include <boost/shared_ptr.hpp>

#include "util.hpp"
#include "movable.hpp"

class Targeter : public Movable {
public:
	typedef boost::shared_ptr<Targeter> ShPtr;

	Targeter();
	void init();
	//void draw();

private:
	DISALLOW_COPY_AND_ASSIGN(Targeter);
};

#endif
