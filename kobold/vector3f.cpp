#include <math.h>

#include "vector3f.hpp"

Vector3f::Vector3f(float xi, float yi, float zi)
    : x(xi),
      y(yi),
      z(zi) {
}

float Vector3f::length() const {
	return sqrt( x * x + y * y + z * z );
}

float Vector3f::distance(const Vector3f& rhs) const {
	return Vector3f(x-rhs.x, y-rhs.y, z-rhs.z).length();
}
