#include "mesh.hpp"

Mesh::Mesh() { }

void Mesh::draw() {
	glVertexPointer(3, GL_FLOAT, 0, &verticies_[0]);
}