#pragma once
#include <glm/glm.hpp>

namespace rt {
	class ray;
	class intersection_info;
	class sphere;

	bool ray_vs_sphere(const sphere& center, const ray& r, intersection_info& ii);
}
