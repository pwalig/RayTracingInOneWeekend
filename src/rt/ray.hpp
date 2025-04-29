#pragma once
#include <glm/glm.hpp>
#include <vector>

#include "sphere.hpp"

namespace rt {
	class hit_info;

	class ray {
	public:
		glm::vec3 orig;
		glm::vec3 dir;
		bool exiting = false;

		//ray() = default;
		inline ray(const glm::vec3& Origin, const glm::vec3& Direction, bool Exiting = false) :
			orig(Origin), dir(Direction), exiting(Exiting) {}

		inline glm::vec3 at(float t) const {
			return dir * t + orig;
		}

		hit_info cast(const std::vector<sphere>& word) const;
	};
}
