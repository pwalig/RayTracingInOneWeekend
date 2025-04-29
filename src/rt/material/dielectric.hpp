#pragma once

#include <glm/glm.hpp>

#include "material.hpp"

namespace rt {
	namespace dielectric {
		bool scatter(
			const ray& r_in,
			const intersection_info& rec,
			const material& mat,
			Rand& gen,
			glm::vec3& attenuation,
			ray& scattered
		);
	}
}
