#include "stairs.hpp"
#include "vector3f.hpp"
#include "vector2f.hpp"

Stairs::Stairs() {
	init();
}

void Stairs::init() {
	//Vector3f::ShPtr v (new Vector3f(-1.0f, -1.0f, 0.0f));
	//verticies_.push_back(v);
	//Top side of stairs
	verticies_.push_back(Vector3f(0.5f, -0.5f, 0.0f));
	verticies_.push_back(Vector3f(0.5f, 0.5f, 0.0f));
	verticies_.push_back(Vector3f(0.16f, 0.5f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));

	verticies_.push_back(Vector3f(0.16f, 0.5f, 0.0f));
	verticies_.push_back(Vector3f(0.16f, -0.5f, 0.0f));
	verticies_.push_back(Vector3f(0.5f, -0.5f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	
	verticies_.push_back(Vector3f(0.16f, -0.5f, -0.166f));
	verticies_.push_back(Vector3f(0.16f, 0.5f, -0.166f));
	verticies_.push_back(Vector3f(-0.17f, 0.5f, -0.166f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));

	verticies_.push_back(Vector3f(-0.17f, 0.5f, -0.166f));
	verticies_.push_back(Vector3f(-0.17f, -0.5f, -0.166f));
	verticies_.push_back(Vector3f(0.16f, -0.5f, -0.166f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	
	verticies_.push_back(Vector3f(-0.17f, -0.5f, -0.333f));
	verticies_.push_back(Vector3f(-0.17f, 0.5f, -0.333f));
	verticies_.push_back(Vector3f(-0.5f, 0.5f, -0.333f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));

	verticies_.push_back(Vector3f(-0.5f, 0.5f, -0.333f));
	verticies_.push_back(Vector3f(-0.5f, -0.5f, -0.333f));
	verticies_.push_back(Vector3f(-0.17f, -0.5f, -0.333f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));

	// top
	verticies_.push_back(Vector3f(0.5f, 0.5f, 0.0f));
	verticies_.push_back(Vector3f(0.5f, 0.5f, -0.166f));
	verticies_.push_back(Vector3f(0.16f, 0.5f, -0.166f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	
	verticies_.push_back(Vector3f(-0.16f, 0.5f, -0.166f));
	verticies_.push_back(Vector3f(-0.16f, 0.5f, 0.0f));
	verticies_.push_back(Vector3f(0.5f, 0.5f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	
	verticies_.push_back(Vector3f(0.5f, 0.5f, -0.166f));
	verticies_.push_back(Vector3f(0.5f, 0.5f, -0.333f));
	verticies_.push_back(Vector3f(-0.17f, 0.5f, -0.333f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	
	verticies_.push_back(Vector3f(-0.17f, 0.5f, -0.333f));
	verticies_.push_back(Vector3f(-0.17f, 0.5f, -0.166f));
	verticies_.push_back(Vector3f(0.5f, 0.5f, -0.166f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	
	verticies_.push_back(Vector3f(0.5f, 0.5f, -0.333f));
	verticies_.push_back(Vector3f(0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vector3f(-0.5f, 0.5f, -0.5f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	
	verticies_.push_back(Vector3f(-0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vector3f(-0.5f, 0.5f, -0.333f));
	verticies_.push_back(Vector3f(0.5f, 0.5f, -0.333f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	
	// back
	verticies_.push_back(Vector3f(-0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vector3f(-0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vector3f(0.5f, 0.5f, -0.5f));
	normals_.push_back(Vector3f(0.0f, 0.0f, -1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, -1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, -1.0f));
	
	verticies_.push_back(Vector3f(0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vector3f(0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vector3f(-0.5f, -0.5f, -0.5f));
	normals_.push_back(Vector3f(0.0f, 0.0f, -1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, -1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, -1.0f));
	
	// left
	verticies_.push_back(Vector3f(-0.5f, -0.5f, -0.333f));
	verticies_.push_back(Vector3f(-0.5f, 0.5f, -0.333));
	verticies_.push_back(Vector3f(-0.5f, 0.5f, -0.5f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	
	verticies_.push_back(Vector3f(-0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vector3f(-0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vector3f(-0.5f, -0.5f, -0.33f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	
	verticies_.push_back(Vector3f(-0.17f, -0.5f, -0.166f));
	verticies_.push_back(Vector3f(-0.17f, 0.5f, -0.166));
	verticies_.push_back(Vector3f(-0.17f, 0.5f, -0.333f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	
	verticies_.push_back(Vector3f(-0.17f, 0.5f, -0.333f));
	verticies_.push_back(Vector3f(-0.17f, -0.5f, -0.333f));
	verticies_.push_back(Vector3f(-0.17f, -0.5f, -0.166f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	
	verticies_.push_back(Vector3f(0.16f, -0.5f, -0.166f));
	verticies_.push_back(Vector3f(0.16f, 0.5f, -0.166f));
	verticies_.push_back(Vector3f(0.16f, 0.5f, 0.0f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	
	verticies_.push_back(Vector3f(0.16f, 0.5f, 0.0f));
	verticies_.push_back(Vector3f(0.16f, -0.5f, 0.0f));
	verticies_.push_back(Vector3f(0.16f, -0.5f, -0.166f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(-1.0f, 0.0f, 0.0f));
	
	// bottom
	verticies_.push_back(Vector3f(-0.5f, -0.5f, -0.333f));
	verticies_.push_back(Vector3f(-0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vector3f(0.5f, -0.5f, -0.5f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	
	verticies_.push_back(Vector3f(0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vector3f(0.5f, -0.5f, -0.333f));
	verticies_.push_back(Vector3f(-0.5f, -0.5f, -0.333f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	
	verticies_.push_back(Vector3f(-0.16f, -0.5f, -0.166f));
	verticies_.push_back(Vector3f(-0.16f, -0.5f, -0.333f));
	verticies_.push_back(Vector3f(0.5f, -0.5f, -0.333f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	
	verticies_.push_back(Vector3f(0.5f, -0.5f, -0.333f));
	verticies_.push_back(Vector3f(0.5f, -0.5f, -0.166f));
	verticies_.push_back(Vector3f(-0.16f, -0.5f, -0.166f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	
	verticies_.push_back(Vector3f(0.17f, -0.5f, 0.0f));
	verticies_.push_back(Vector3f(0.17f, -0.5f, -0.166f));
	verticies_.push_back(Vector3f(0.5f, -0.5f, -0.166f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	
	verticies_.push_back(Vector3f(0.5f, -0.5f, -0.166f));
	verticies_.push_back(Vector3f(0.5f, -0.5f, 0.0f));
	verticies_.push_back(Vector3f(0.17f, -0.5f, 0.0f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, -1.0f, 0.0f));
	
	// right
	verticies_.push_back(Vector3f(0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vector3f(0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vector3f(0.5f, 0.5f, 0.0f));
	normals_.push_back(Vector3f(1.0f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(1.0f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(1.0f, 0.0f, 0.0f));
	
	verticies_.push_back(Vector3f(0.5f, 0.5f, 0.0f));
	verticies_.push_back(Vector3f(0.5f, -0.5f, 0.0f));
	verticies_.push_back(Vector3f(0.5f, -0.5f, -0.0f));
	normals_.push_back(Vector3f(1.0f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(1.0f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(1.0f, 0.0f, 0.0f));
	
	for (int i = 0; i < 12; ++i) {
		tex_coords_.push_back(Vector2f(1.0f, 1.0f));
		tex_coords_.push_back(Vector2f(1.0f, 0.0f));
		tex_coords_.push_back(Vector2f(0.0f, 0.0f));
		tex_coords_.push_back(Vector2f(0.0f, 0.0f));
		tex_coords_.push_back(Vector2f(0.0f, 1.0f));
		tex_coords_.push_back(Vector2f(1.0f, 1.0f));
	}
	/*for (int i = 0; i < 6; ++i) {
		tex_coords_.push_back(Vector2f(0.5f, 0.5f));
		tex_coords_.push_back(Vector2f(0.5f, 0.0f));
		tex_coords_.push_back(Vector2f(0.0f, 0.0f));
		tex_coords_.push_back(Vector2f(0.0f, 0.0f));
		tex_coords_.push_back(Vector2f(0.0f, 0.5f));
		tex_coords_.push_back(Vector2f(0.5f, 0.5f));
	}*/
}

int Stairs::triangle_count() {
	return 24;
}
