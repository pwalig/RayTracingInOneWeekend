#pragma once

#include <glm/glm.hpp>

#include "material.hpp"

namespace rt {
	namespace lambertian {
		bool scatter(
			ray& r,
			const hit_info& rec,
            const material& mat,
			Rand& gen,
			glm::vec3& attenuation
		);
	}
}
