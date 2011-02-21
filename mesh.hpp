#ifndef NDG_MESH_H_
#define NDG_MESH_H_

#include <boost/shared_ptr.hpp>
#include <vector>

#include "SDL/SDL.h"
#include "SDL/SDL_opengl.h"

#include "basetypes.hpp"
#include "vector2f.hpp"
#include "vector3f.hpp"

class Mesh {
public:
	typedef boost::shared_ptr<Mesh> ShPtr;

	Mesh();
	void draw();
	virtual int triangle_count() = 0;

protected:
	std::vector<Vector3f> verticies_;
	std::vector<Vector2f> tex_coords_;

private:	
	DISALLOW_COPY_AND_ASSIGN(Mesh);
};

#endif
