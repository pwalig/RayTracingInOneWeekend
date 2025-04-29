#include "lambert.hpp"

#include "../ray.hpp"
#include "../intersection_info.hpp"

bool rt::lambertian::scatter(
	const ray& r_in,
	const intersection_info& ii,
	const material& mat,
	Rand& gen,
	glm::vec3& attenuation,
	ray& scattered
) {
	glm::vec3 scatter_direction = ii.normal + random_vector(gen);
	if (glm::length(scatter_direction) < 0.000001f)
		scatter_direction = ii.normal;
	else scatter_direction = glm::normalize(scatter_direction);
	scattered = ray(ii.point, scatter_direction);
	attenuation = mat.albedo;
	return true;
}
