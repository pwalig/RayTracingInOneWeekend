#include "lambert.hpp"

#include "../ray.hpp"
#include "../hit_info.hpp"

bool rt::lambertian::scatter(
	ray& r,
	const hit_info& ii,
	const material& mat,
	Rand& gen,
	glm::vec3& attenuation
) {
	glm::vec3 scatter_direction = ii.normal + random_vector(gen);
	if (glm::length(scatter_direction) < 0.000001f)
		scatter_direction = ii.normal;
	else scatter_direction = glm::normalize(scatter_direction);
	r = ray(ii.point, scatter_direction, r.exiting);
	attenuation = mat.albedo;
	return true;
}
