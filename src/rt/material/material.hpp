#pragma once
#include <functional>

#include <glm/fwd.hpp>

#include "../random.hpp"

namespace rt {
    class ray;
    class hit_info;

    class material {
    public:
        using scatter_function = bool(*)(
			ray& r,
			const hit_info& rec,
            const material& mat,
			Rand& gen,
			glm::vec3& attenuation
		);

        scatter_function scatter_func;
        glm::vec3 albedo;
        float fuzz;

        inline material(
            scatter_function Scatter,
            const glm::vec3& Albedo = glm::vec3(1.0f),
            float Fuzz = 0.0f
        ) : scatter_func(Scatter), albedo(Albedo), fuzz(Fuzz) {}

        inline bool scatter(
            ray& r,
            const hit_info& rec,
            Rand& gen,
            glm::vec3& attenuation
        ) {
            return scatter_func(r, rec, *this, gen, attenuation);
        }
    };
}
