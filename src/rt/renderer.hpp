#pragma once
#include <vector>
#include <random>

#include <glm/glm.hpp>

#include "types.hpp"
#include "sphere.hpp"
#include "material/material.hpp"
#include "material/lambert.hpp"

namespace rt {
	class ray;
	class renderer {
	public:
		Rand gen;
		std::vector<sphere> world;
		std::vector<material> materials;

		inline static float gamma_correction(float value, float gamma = 2.2f) {
			if (value > 0.0f) {
				return std::pow(value, 1.0f / gamma);
			}
			return 0.0f;
		}

		inline static glm::vec3 gamma_correction(const glm::vec3& value, float gamma = 2.2f) {
			return glm::vec3(
				gamma_correction(value.x, gamma),
				gamma_correction(value.y, gamma),
				gamma_correction(value.z, gamma)
			);
		}

		glm::vec3 ray_color(const ray& r, u32 depth = 8);
	};
}
