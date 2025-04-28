#pragma once
#include <glm/glm.hpp>

namespace rt {
	class intersection_info {
	public:
		glm::vec3 normal;
		float distance;

		inline intersection_info() : normal(glm::vec3(0.0f)), distance(std::numeric_limits<float>::max()) {}
	};
}