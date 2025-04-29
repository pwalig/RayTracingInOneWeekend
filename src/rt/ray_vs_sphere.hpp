#pragma once
#include <glm/glm.hpp>

namespace rt {
	class ray;
	class sphere;
	class hit_info;

	bool ray_vs_sphere(const sphere& center, const ray& r, hit_info& ii);
	bool ray_vs_sphere_exit(const sphere& center, const ray& r, hit_info& ii);
}
