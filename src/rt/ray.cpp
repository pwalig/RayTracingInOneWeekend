#include "ray.hpp"
#include "ray_vs_sphere.hpp"
#include "intersection_info.hpp"

glm::vec3 rt::ray::color() const
{
	intersection_info ii;
	glm::vec3 spherePos(0.0f, 0.0f, 1.0f);
	if (ray_vs_sphere(spherePos, 0.5f, *this, ii)) {
		return 0.5f * (ii.normal + glm::vec3(1.0f));
	}
	else return glm::vec3(0.0f);
}
