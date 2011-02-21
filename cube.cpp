#include "cube.hpp"
#include "vertex.hpp"

Cube::Cube() {
	init();
}

void Cube::init() {
	//Vertex::ShPtr v (new Vertex(-1.0f, -1.0f, 0.0f));
	//verticies_.push_back(v);
	verticies_.push_back(Vertex(0.5f, -0.5f, 0.5f));
	verticies_.push_back(Vertex(0.5f, 0.5f, 0.5f));
	verticies_.push_back(Vertex(-0.5f, 0.5f, 0.5f));

	verticies_.push_back(Vertex(-0.5f, 0.5f, 0.5f));
	verticies_.push_back(Vertex(-0.5f, -0.5f, 0.5f));
	verticies_.push_back(Vertex(0.5f, -0.5f, 0.5f));

	// top
	verticies_.push_back(Vertex(0.5f, 0.5f, 0.5f));
	verticies_.push_back(Vertex(-0.5f, 0.5f, 0.5f));
	verticies_.push_back(Vertex(0.5f, 0.5f, -0.5f));
	
	verticies_.push_back(Vertex(-0.5f, 0.5f, 0.5f));
	verticies_.push_back(Vertex(0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vertex(-0.5f, 0.5f, -0.5f));
	
	// back
	verticies_.push_back(Vertex(0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vertex(-0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vertex(-0.5f, -0.5f, -0.5f));
	
	verticies_.push_back(Vertex(0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vertex(-0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vertex(0.5f, -0.5f, -0.5f));
	
	// left
	verticies_.push_back(Vertex(-0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vertex(-0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vertex(-0.5f, 0.5f, 0.5f));
	
	verticies_.push_back(Vertex(-0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vertex(-0.5f, 0.5f, 0.5f));
	verticies_.push_back(Vertex(-0.5f, -0.5f, 0.5f));
	
	// bottom
	verticies_.push_back(Vertex(-0.5f, -0.5f, 0.5f));
	verticies_.push_back(Vertex(0.5f, -0.5f, 0.5f));
	verticies_.push_back(Vertex(0.5f, -0.5f, -0.5f));
	
	verticies_.push_back(Vertex(-0.5f, -0.5f, 0.5f));
	verticies_.push_back(Vertex(0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vertex(-0.5f, -0.5f, -0.5f));
	
	// right
	verticies_.push_back(Vertex(0.5f, -0.5f, 0.5f));
	verticies_.push_back(Vertex(0.5f, -0.5f, -0.5f));
	verticies_.push_back(Vertex(0.5f, 0.5f, -0.5f));
	
	verticies_.push_back(Vertex(0.5f, -0.5f, 0.5f));
	verticies_.push_back(Vertex(0.5f, 0.5f, -0.5f));
	verticies_.push_back(Vertex(0.5f, 0.5f, 0.5f));	
}

int Cube::triangle_count() {
	return 12;
}
