#include "ray_vs_sphere.hpp"
#include "ray.hpp"
#include "intersection_info.hpp"

bool rt::ray_vs_sphere(const glm::vec3& center, float radius, const ray& r, intersection_info& ii) {
	glm::vec3 oc = center - r.orig;
	float h = glm::dot(r.dir, oc);
	float c = glm::dot(oc, oc) - radius * radius;
	float delta = h*h - c;

	if (delta < 0) return false;

	float t1 = h - std::sqrt(delta);
	if (t1 >= 0.0f && t1 < ii.distance) {
		ii.distance = t1;
		ii.point = r.at(t1);
		ii.normal = glm::normalize(ii.point - center);
		return true;
	}

	return false;
}
