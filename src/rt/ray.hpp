#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "sphere.hpp"

namespace rt {
	class intersection_info;

	class ray {
	public:
		glm::vec3 orig;
		glm::vec3 dir;

		ray() = default;
		inline ray(const glm::vec3& Origin, const glm::vec3& Direction) : orig(Origin), dir(Direction) {}

		inline glm::vec3 at(float t) const {
			return dir * t + orig;
		}

		intersection_info cast(const std::vector<sphere>& word) const;
	};
}
