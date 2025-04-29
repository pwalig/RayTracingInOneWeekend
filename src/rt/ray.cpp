#include "ray.hpp"

#include "ray_vs_sphere.hpp"
#include "hit_info.hpp"

rt::hit_info rt::ray::cast(const std::vector<rt::sphere>& word) const
{
	hit_info ii;
	if (exiting) {
		for (const sphere& sphere : word) {
			ray_vs_sphere_exit(sphere, *this, ii);
		}
	}
	else {
		for (const sphere& sphere : word) {
			ray_vs_sphere(sphere, *this, ii);
		}
	}
	return ii;
}
