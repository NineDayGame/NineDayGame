#ifndef NDG_MESH_H_
#define NDG_MESH_H_

#include <boost/shared_ptr.hpp>
#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "basetypes.hpp"
#include "vertex.hpp"

class Mesh {
public:
	typedef boost::shared_ptr<Mesh> ShPtr;

	Mesh();
	void draw();

protected:
	std::vector<Vertex> verticies_;

private:	
	DISALLOW_COPY_AND_ASSIGN(Mesh);
};

#endif
