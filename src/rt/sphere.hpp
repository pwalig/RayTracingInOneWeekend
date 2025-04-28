#pragma once
#include <glm/glm.hpp>

#include "types.hpp"

namespace rt {
	class sphere {
	public:
		glm::vec3 pos;
		u32 material;
		float radius;

		inline sphere(const glm::vec3& Position, float Radius, u32 Material) :
			pos(Position), radius(Radius), material(Material) { }
	};
}
