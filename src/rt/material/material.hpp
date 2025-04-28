#pragma once
#include <functional>

#include <glm/fwd.hpp>

#include "random.hpp"

namespace rt {
    class ray;
    class intersection_info;

    class material {
    public:
        using scatter_function =
            std::function<bool(
                const ray& r_in,
                const intersection_info& rec,
                Rand& gen,
                glm::vec3& attenuation,
                ray& scattered
                )>;

        scatter_function scatter;

        inline material(const scatter_function& Scatter) : scatter(Scatter) {}
    };
}
