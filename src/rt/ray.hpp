#pragma once
#include <glm/glm.hpp>

namespace rt {
	class ray {
	public:
		glm::vec3 orig;
		glm::vec3 dir;

		inline ray(const glm::vec3& Origin, const glm::vec3& Direction) : orig(Origin), dir(Direction) {}

		inline glm::vec3 at(float t) const {
			return dir * t + orig;
		}

		glm::vec3 color() const;
	};
}
