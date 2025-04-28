#include <iostream>
#include <random>

#include "rt/image.hpp"
#include "rt/ray.hpp"
#include "rt/camera.hpp"
#include "rt/intersection_info.hpp"

#include "matrix.hpp"

using namespace rt;

int main() {

    u8 samples = 4;
    //image img(300, 200);
    matrix<glm::vec3> img(480, 320, glm::vec3(0.0f));
    camera cam(glm::vec3(0.0f, 0.0f, -10.0f), img.x(), img.y(), 1.0f, 0.5f);
    std::vector<sphere> word = {
        sphere(glm::vec3(0.0f, 0.0f, 1.0f), 0.5f),
        sphere(glm::vec3(0.0f, -10.5f, 1.0f), 10.0f)
    };


    glm::vec3 pixel0 = cam.pixel0();

    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());

	for (u32 i = 0; i < img.x(); i++) {
		for (u32 j = 0; j < img.y(); j++) {
            for (u8 sample = 0; sample < samples; sample++) {
                std::uniform_real_distribution<float> xdist(-0.5f, 0.5f);
                glm::vec2 coord(xdist(gen) + i, xdist(gen) + j);
				glm::vec3 pixelCenter = pixel0 + glm::vec3(coord.x * cam.delta.x, coord.y * cam.delta.y, 0.0f);
				glm::vec3 rayDir = pixelCenter - cam.pos;
				ray r(cam.pos, glm::normalize(rayDir));
				intersection_info ii = r.cast(word);
				img[i][j] += 0.5f * (ii.normal + glm::vec3(1.0f));
            }
            img[i][j] /= samples;
        }
    }

    image(img).to_png("out.png");
}