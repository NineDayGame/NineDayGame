#include "block.hpp"
#include "cube.hpp"
#include "vector3f.hpp"

Block::Block() {
	init();
}

void Block::init() {
	mesh_.reset(new Cube());
	set_color(Vector3f(0.5f, 0.5f, 0.5f));
}
