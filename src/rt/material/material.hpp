#pragma once
#include <functional>

#include <glm/fwd.hpp>

#include "random.hpp"

namespace rt {
    class ray;
    class intersection_info;

    class material {
    public:
        using scatter_function = bool(*)(
			const ray& r_in,
			const intersection_info& rec,
            const material& mat,
			Rand& gen,
			glm::vec3& attenuation,
			ray& scattered
		);

        scatter_function scatter_func;
        glm::vec3 albedo;

        inline material(scatter_function Scatter, const glm::vec3& Albedo) :
            scatter_func(Scatter), albedo(Albedo) {}

        inline bool scatter(
            const ray& r_in,
            const intersection_info& rec,
            Rand& gen,
            glm::vec3& attenuation,
            ray& scattered
        ) {
            return scatter_func(r_in, rec, *this, gen, attenuation, scattered);
        }
    };
}
