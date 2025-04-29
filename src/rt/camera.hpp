#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "ray.hpp"
#include "types.hpp"
#include "random.hpp"

namespace rt {
	class camera {
	public:
		glm::quat rot = glm::quat();
		glm::vec3 pos = glm::vec3();
		glm::vec2 viewport = glm::vec2();
		glm::vec3 offset = glm::vec3();
		glm::vec2 delta = glm::vec2();
		float defocus;

		camera(
			glm::vec3 Position, glm::vec3 lookAt,
			u32 width, u32 height,
			float fov, float focal, float blur = 0.0f
		);

		inline glm::vec3 pixel0() const {
			return pos + offset + glm::vec3(0.5f * delta, 0.0f);
		}

		ray get_ray(u32 x, u32 j, Rand& gen) const;

	};
}
