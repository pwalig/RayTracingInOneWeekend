#pragma once
#include <random>

#include <glm/glm.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/gtx/quaternion.hpp>

namespace rt {
	using Rand = std::mt19937;

	inline static glm::vec3 random_vector(Rand& eng) {
		std::uniform_real_distribution<float> distrib(-glm::pi<float>(), glm::pi<float>());
		glm::quat rot(glm::vec3(distrib(eng), distrib(eng), 0.0f));
		return glm::vec3(0.0f, 0.0f, 1.0f) * rot;
	}

	inline static glm::vec3 random_on_hemisphere(const glm::vec3& normal, Rand& eng) {
		std::uniform_real_distribution<float> distrib(-glm::pi<float>() / 2.0f, glm::pi<float>() / 2.0f);
		glm::quat rot(glm::vec3(distrib(eng), distrib(eng), 0.0f));
		return normal * rot;
	}
}

