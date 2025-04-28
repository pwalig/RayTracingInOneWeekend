#pragma once
#include <glm/glm.hpp>

namespace rt {
	class ray;
	class intersection_info;

	bool ray_vs_sphere(const glm::vec3& center, float radius, const ray& r, intersection_info& ii);
}
