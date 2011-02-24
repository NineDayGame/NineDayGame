#include "rect.hpp"
#include "vector3f.hpp"
#include "vector2f.hpp"

Rect::Rect() {
	init();
}

void Rect::init() {

	verticies_.push_back(Vector3f(0.5f, 0.0f, 0.0f));
	verticies_.push_back(Vector3f(0.5f, 1.0f, 0.0f));
	verticies_.push_back(Vector3f(-0.5f, 1.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));

	verticies_.push_back(Vector3f(-0.5f, 1.0f, 0.0f));
	verticies_.push_back(Vector3f(-0.5f, 0.0f, 0.0f));
	verticies_.push_back(Vector3f(0.5f, 0.0f, 0.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	normals_.push_back(Vector3f(0.0f, 0.0f, 1.0f));
	
	tex_coords_.push_back(Vector2f(1.0f, 1.0f));
	tex_coords_.push_back(Vector2f(1.0f, 0.0f));
	tex_coords_.push_back(Vector2f(0.0f, 0.0f));
	tex_coords_.push_back(Vector2f(0.0f, 0.0f));
	tex_coords_.push_back(Vector2f(0.0f, 1.0f));
	tex_coords_.push_back(Vector2f(1.0f, 1.0f));
	/*tex_coords_.push_back(Vector2f(5*0.0625f, 1*0.0625f));
	tex_coords_.push_back(Vector2f(5*0.0625f, 0.0f));
	tex_coords_.push_back(Vector2f(4*0.0625f, 0.0f));
	tex_coords_.push_back(Vector2f(4*0.0625f, 0.0f));
	tex_coords_.push_back(Vector2f(4*0.0625f, 1*0.0625f));
	tex_coords_.push_back(Vector2f(5*0.0625f, 1*0.0625f));*/
}

int Rect::triangle_count() {
	return 2;
}
