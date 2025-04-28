#include "lambert.hpp"

#include "../ray.hpp"
#include "../intersection_info.hpp"

rt::material::scatter_function rt::lambertian::scatter(const glm::vec3& albedo)
 {
	return [albedo](
		const ray& r_in,
		const intersection_info& ii,
		Rand& gen,
		glm::vec3& attenuation,
		ray& scattered
	) {
		glm::vec3 scatter_direction = ii.normal + random_vector(gen);
		if (glm::length(scatter_direction) < 0.000001f)
			scatter_direction = ii.normal;
		scattered = ray(ii.point, scatter_direction);
		attenuation = albedo;
		return true;
	};

}
