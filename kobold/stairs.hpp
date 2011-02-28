#ifndef NDG_STAIRS_H_
#define NDG_STAIRS_H_

#include <boost/shared_ptr.hpp>

#include "util.hpp"
#include "mesh.hpp"

class Stairs : public Mesh {
public:
	typedef boost::shared_ptr<Stairs> ShPtr;

	Stairs();
	void init();
	int triangle_count();

private:
	DISALLOW_COPY_AND_ASSIGN(Stairs);
};

#endif
