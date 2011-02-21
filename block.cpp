#include "block.hpp"
#include "vertex.hpp"

Block::Block() {
	init();
}

void Block::init() {
	mesh_.reset(new Cube());
	set_color(Vertex(0.5f, 0.5f, 0.5f));
}
