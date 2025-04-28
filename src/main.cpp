#include <iostream>
#include <random>

#include <glm/gtx/quaternion.hpp>

#include "rt/image.hpp"
#include "rt/ray.hpp"
#include "rt/camera.hpp"
#include "rt/intersection_info.hpp"

#include "matrix.hpp"

using namespace rt;

inline float gamma(float value) {
    if (value > 0.0f) {
        return std::pow(value, 1.0f / 2.2f);
    }
    return 0.0f;
}

inline glm::vec3 gamma(const glm::vec3& value) {
    return glm::vec3(
        gamma(value.x),
        gamma(value.y),
        gamma(value.z)
    );
}

template <typename Engine>
inline glm::vec3 random_on_hemisphere(const glm::vec3& normal, Engine& eng) {
	std::uniform_real_distribution<float> distrib(-glm::pi<float>() / 2.0f, glm::pi<float>() / 2.0f);
    glm::quat rot(glm::vec3(distrib(eng), distrib(eng), 0.0f));
    return normal * rot;
}

template <typename Engine>
inline glm::vec3 random_vector(Engine& eng) {
	std::uniform_real_distribution<float> distrib(-glm::pi<float>(), glm::pi<float>());
    glm::quat rot(glm::vec3(distrib(eng), distrib(eng), 0.0f));
    return glm::vec3(0.0f, 0.0f, 1.0f) * rot;
}

template <typename Engine>
glm::vec3 ray_color(const ray& r, const std::vector<sphere>& world, Engine& eng, u32 depth = 8) {
    if (depth == 0) return glm::vec3(0.0f);

	intersection_info ii = r.cast(world);
    if (ii.hit()) {
        glm::vec3 dir = ii.normal + random_vector(eng);
        return 0.5f * ray_color(ray(ii.point, dir), world, eng, depth - 1);
    }
	float a = 0.5*(r.dir.y + 1.0);
	return (1.0f-a)*glm::vec3(1.0f, 1.0f, 1.0f) + a*glm::vec3(0.5f, 0.7f, 1.0f);
}

int main() {

    u8 samples = 10;
    matrix<glm::vec3> img(480, 320, glm::vec3(0.0f));
    camera cam(glm::vec3(0.0f, 0.0f, -4.0f), img.x(), img.y(), 1.0f, 0.5f);
    std::vector<sphere> world = {
        sphere(glm::vec3(0.0f, 0.0f, 1.0f), 0.5f),
        sphere(glm::vec3(0.0f, -10.5f, 1.0f), 10.0f)
    };


    glm::vec3 pixel0 = cam.pixel0();

    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());

	for (u32 i = 0; i < img.x(); i++) {
		std::clog << "\rScanlines remaining: " << (img.x() - i) << ' ' << std::flush;
		for (u32 j = 0; j < img.y(); j++) {
            for (u8 sample = 0; sample < samples; sample++) {
                std::uniform_real_distribution<float> xdist(-0.5f, 0.5f);
                glm::vec2 coord(xdist(gen) + i, xdist(gen) + j);
				glm::vec3 pixelCenter = pixel0 + glm::vec3(coord.x * cam.delta.x, coord.y * cam.delta.y, 0.0f);
				glm::vec3 rayDir = pixelCenter - cam.pos;
				ray r(cam.pos, glm::normalize(rayDir));
				img[i][j] += ray_color(r, world, gen);
            }
            img[i][j] /= samples;
            img[i][j] = gamma(img[i][j]);
        }
    }
    std::clog << "\rDone.                 \n";

    image(img).to_png("out.png");
}