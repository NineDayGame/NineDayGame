#ifndef NDG_CUBE_H_
#define NDG_CUBE_H_

#include <boost/shared_ptr.hpp>

#include "basetypes.hpp"
#include "mesh.hpp"

class Cube : public Mesh {
public:
	typedef boost::shared_ptr<Cube> ShPtr;

	Cube();
	void init();
	int triangle_count();

private:
	DISALLOW_COPY_AND_ASSIGN(Cube);
};

#endif
