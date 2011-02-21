#include "cube.hpp"
#include "vector3f.hpp"
#include "vector2f.hpp"

Cube::Cube() {
	init();
}

void Cube::init() {
	//Vector3f::ShPtr v (new Vector3f(-1.0f, -1.0f, 0.0f));
	//verticies_.push_back(v);
	verticies_.push_back(Vector3f(0.5f, -0.5f, 0.5f));
	verticies_.push_back(Vector3f(0.5f, 0.5f, 0.5f));
	verticies_.push_back(Vector3f(-0.5f, 0.5f, 0.5f));

	verticies_.push_back(Vector3f(-0.5f, 0.5f, 0.5f));
	verticies_.push_back(Vector3f(-0.5f, -0.5f, 0.5f));
	verticies_.push_back(Vector3f(0.5f, -0.5f, 0.5f));

	// top
	verticies_.push_back(Vector3f(0.5f, 0.5f, 0.5f));
	verticies_.push_back(Vector3f(0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vector3f(-0.5f, 0.5f, -0.5f));
	
	verticies_.push_back(Vector3f(-0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vector3f(-0.5f, 0.5f, 0.5f));
	verticies_.push_back(Vector3f(0.5f, 0.5f, 0.5f));
	
	// back
	verticies_.push_back(Vector3f(-0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vector3f(-0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vector3f(0.5f, 0.5f, -0.5f));
	
	verticies_.push_back(Vector3f(0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vector3f(0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vector3f(-0.5f, -0.5f, -0.5f));
	
	// left
	verticies_.push_back(Vector3f(-0.5f, -0.5f, 0.5f));
	verticies_.push_back(Vector3f(-0.5f, 0.5f, 0.5f));
	verticies_.push_back(Vector3f(-0.5f, 0.5f, -0.5f));
	
	verticies_.push_back(Vector3f(-0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vector3f(-0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vector3f(-0.5f, -0.5f, 0.5f));
	
	// bottom
	verticies_.push_back(Vector3f(-0.5f, -0.5f, 0.5f));
	verticies_.push_back(Vector3f(-0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vector3f(0.5f, -0.5f, -0.5f));
	
	verticies_.push_back(Vector3f(0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vector3f(0.5f, -0.5f, 0.5f));
	verticies_.push_back(Vector3f(-0.5f, -0.5f, 0.5f));
	
	// right
	verticies_.push_back(Vector3f(0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vector3f(0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vector3f(0.5f, 0.5f, 0.5f));
	
	verticies_.push_back(Vector3f(0.5f, 0.5f, 0.5f));
	verticies_.push_back(Vector3f(0.5f, -0.5f, 0.5f));
	verticies_.push_back(Vector3f(0.5f, -0.5f, -0.5f));
	
	for (int i = 0; i < 6; ++i) {
		tex_coords_.push_back(Vector2f(1.0f, 1.0f));
		tex_coords_.push_back(Vector2f(1.0f, 0.0f));
		tex_coords_.push_back(Vector2f(0.0f, 0.0f));
		tex_coords_.push_back(Vector2f(0.0f, 0.0f));
		tex_coords_.push_back(Vector2f(0.0f, 1.0f));
		tex_coords_.push_back(Vector2f(1.0f, 1.0f));
	}
}

int Cube::triangle_count() {
	return 12;
}
