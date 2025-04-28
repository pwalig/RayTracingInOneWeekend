#pragma once
#include <glm/glm.hpp>

namespace rt {
	class camera {
	private:
		using u32 = uint32_t;
	public:
		glm::vec3 pos = glm::vec3();
		glm::vec2 viewport = glm::vec2();
		glm::vec3 offset = glm::vec3();
		glm::vec2 delta = glm::vec2();

		inline camera(glm::vec3 Position, u32 width, u32 height, float focal, float scale) :
			pos(Position),
			viewport(scale * (float(width) / height), scale),
			offset(viewport.x / 2.0f, viewport.y / 2.0f, focal),
			delta(-viewport.x / width, -viewport.y / height)
		{ }

		inline glm::vec3 pixel0() const {
			glm::vec3 upper_left = pos + offset;
			return upper_left + glm::vec3(0.5f * delta, 0.0f);
		}

	};
}
