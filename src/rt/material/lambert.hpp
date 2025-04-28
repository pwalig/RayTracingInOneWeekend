#pragma once

#include <glm/glm.hpp>

#include "material.hpp"

namespace rt {
	namespace lambertian {
		material::scatter_function scatter(const glm::vec3& albedo);
	}
}
