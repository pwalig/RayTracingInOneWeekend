#pragma once
#include <glm/glm.hpp>

#include "types.hpp"

namespace rt {
	class hit_info {
	public:
		glm::vec3 normal;
		glm::vec3 point;
		u32 material;
		float distance;

		inline hit_info() :
			normal(glm::vec3(0.0f)), point(glm::vec3(0.0f)),
			distance(std::numeric_limits<float>::max()), material(0) {}
		inline bool hit() const {
			return distance != std::numeric_limits<float>::max();
		}
	};
}