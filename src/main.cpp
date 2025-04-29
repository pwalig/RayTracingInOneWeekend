#include <iostream>


#include "rt/image.hpp"
#include "rt/ray.hpp"
#include "rt/camera.hpp"
#include "rt/renderer.hpp"
#include "rt/material/metal.hpp"
#include "rt/material/lambert.hpp"
#include "rt/material/dielectric.hpp"

#include "matrix.hpp"

using namespace rt;

int main() {
    u8 samples = 10;
    matrix<glm::vec3> img(480, 320, glm::vec3(0.0f));
    glm::vec3 campos = glm::vec3(-13.0f, 2.0f, -3.0f);
    camera cam(
        campos,
        glm::vec3(0.0f, 0.0f, 0.0f),
		img.x(), img.y(), 20.0f, 10.0f, 0.6f
	);

    renderer rend;
    std::random_device randomDevice;
    rend.gen = std::mt19937(randomDevice());
    rend.world = {
        sphere(glm::vec3(0.0f, -1000.0f, 0.0f), 1000.0f, 0),
        sphere(glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, 3),
        sphere(glm::vec3(-4.0f, 1.0f, 0.0f), 1.0f, 2),
        sphere(glm::vec3(4.0f, 1.0f, 0.0f), 1.0f, 1),
    };
    rend.materials = {
		material(lambertian::scatter, glm::vec3(0.5f, 0.5f, 0.5f)),
		material(lambertian::scatter, glm::vec3(0.4f, 0.2f, 0.1f)),
		material(metal::scatter, glm::vec3(0.7f, 0.6f, 0.5f), 0.0f),
		material(dielectric::scatter, glm::vec3(1.0f), 1.5f),
	};

    std::uniform_real_distribution<float> albdist(0.0f, 1.0f);
	for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = albdist(rend.gen);
            glm::vec3 center(a + 0.9*albdist(rend.gen), 0.2, b + 0.9*albdist(rend.gen));

            if ((center - glm::vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
                if (choose_mat < 0.8) {
					rend.materials.push_back(material(lambertian::scatter, glm::vec3(albdist(rend.gen), albdist(rend.gen), albdist(rend.gen))));
					rend.world.push_back(sphere(center, 0.2f, rend.materials.size() - 1));
                } else if (choose_mat < 0.95) {
					rend.materials.push_back(material(metal::scatter, glm::vec3(albdist(rend.gen), albdist(rend.gen), albdist(rend.gen)), albdist(rend.gen)));
					rend.world.push_back(sphere(center, 0.2f, rend.materials.size() - 1));
                } else {
					rend.world.push_back(sphere(center, 0.2f, 3));
                }

            }
        }
    }

    //glm::vec3 pixel0 = cam.pixel0();

	for (u32 i = 0; i < img.x(); i++) {
		std::clog << "\rScanlines remaining: " << (img.x() - i) << ' ' << std::flush;
		for (u32 j = 0; j < img.y(); j++) {
            for (u8 sample = 0; sample < samples; sample++) {
                ray r = cam.get_ray(i, j, rend.gen);
				img[i][j] += rend.ray_color(r);
            }
            img[i][j] /= samples;
            img[i][j] = renderer::gamma_correction(img[i][j]);
        }
    }
    std::clog << "\rDone.                 \n";

    image(img).to_png("out.png");
}