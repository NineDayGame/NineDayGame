#include "stairway.hpp"
#include "stairs.hpp"
#include "vector3f.hpp"

Stairway::Stairway() {
	init();
}

void Stairway::init() {
	mesh_.reset(new Stairs());
	set_color(Vector3f(0.5f, 0.5f, 0.5f));
}
