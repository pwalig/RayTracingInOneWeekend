#include "ray.hpp"

#include "ray_vs_sphere.hpp"
#include "intersection_info.hpp"

rt::intersection_info rt::ray::cast(const std::vector<rt::sphere>& word) const
{
	intersection_info ii;
	for (const sphere& sphere : word) {
		ray_vs_sphere(sphere, *this, ii);
	}
	return ii;
}
