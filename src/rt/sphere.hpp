#pragma once
#include <glm/glm.hpp>

namespace rt {
	class sphere {
	public:
		glm::vec3 pos;
		float radius;

		inline sphere(const glm::vec3& Position, float Radius) :
			pos(Position), radius(Radius) { }
	};
}
