#include <iostream>


#include "rt/image.hpp"
#include "rt/ray.hpp"
#include "rt/camera.hpp"
#include "rt/intersection_info.hpp"
#include "rt/renderer.hpp"

#include "matrix.hpp"

using namespace rt;

int main() {
    u8 samples = 10;
    matrix<glm::vec3> img(480, 320, glm::vec3(0.0f));
    camera cam(glm::vec3(0.0f, 0.0f, -4.0f), img.x(), img.y(), 1.0f, 0.5f);

    renderer rend;
    rend.world = {
        sphere(glm::vec3(0.0f, 0.0f, 1.0f), 0.5f, 1),
        sphere(glm::vec3(0.0f, -10.5f, 1.0f), 10.0f, 0)
    };
    rend.materials = {
		material(lambertian::scatter(glm::vec3(0.8f, 0.8f, 0.0f))),
		material(lambertian::scatter(glm::vec3(0.1f, 0.2f, 0.5f)))
	};



    glm::vec3 pixel0 = cam.pixel0();

    std::random_device randomDevice;
    rend.gen = std::mt19937(randomDevice());

	for (u32 i = 0; i < img.x(); i++) {
		std::clog << "\rScanlines remaining: " << (img.x() - i) << ' ' << std::flush;
		for (u32 j = 0; j < img.y(); j++) {
            for (u8 sample = 0; sample < samples; sample++) {
                std::uniform_real_distribution<float> xdist(-0.5f, 0.5f);
                glm::vec2 coord(xdist(rend.gen) + i, xdist(rend.gen) + j);
				glm::vec3 pixelCenter = pixel0 + glm::vec3(coord.x * cam.delta.x, coord.y * cam.delta.y, 0.0f);
				glm::vec3 rayDir = pixelCenter - cam.pos;
				ray r(cam.pos, glm::normalize(rayDir));
				img[i][j] += rend.ray_color(r);
            }
            img[i][j] /= samples;
            img[i][j] = renderer::gamma_correction(img[i][j]);
        }
    }
    std::clog << "\rDone.                 \n";

    image(img).to_png("out.png");
}