#include <iostream>
#include <thread>


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
    u8 samples = 500;
    matrix<glm::vec3> img(1200, 675, glm::vec3(0.0f));
    glm::vec3 campos = glm::vec3(-13.0f, 2.0f, -3.0f);
    camera cam(
        campos,
        glm::vec3(0.0f, 0.0f, 0.0f),
		img.x(), img.y(), 20.0f, 10.0f, 0.6f
	);

    renderer rend;
    std::random_device randomDevice;
    std::mt19937 gen(2);
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
            auto choose_mat = albdist(gen);
            glm::vec3 center(a + 0.9*albdist(gen), 0.2, b + 0.9*albdist(gen));

            if ((center - glm::vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f) {
                glm::vec3 albedo = glm::vec3(albdist(gen), albdist(gen), albdist(gen));
                albedo.x *= albedo.x;
                albedo.y *= albedo.y;
                albedo.z *= albedo.z;
                if (choose_mat < 0.8) {
					rend.materials.push_back(material(lambertian::scatter, albedo));
					rend.world.push_back(sphere(center, 0.2f, rend.materials.size() - 1));
                } else if (choose_mat < 0.95) {
					rend.materials.push_back(material(metal::scatter, albedo, albdist(gen)));
					rend.world.push_back(sphere(center, 0.2f, rend.materials.size() - 1));
                } else {
					rend.world.push_back(sphere(center, 0.2f, 3));
                }

            }
        }
    }

    std::vector<std::thread> threads;
    u32 concurency = std::thread::hardware_concurrency();
    std::cout << concurency << '\n';
    threads.reserve(concurency);
    for (u32 th = 0; th < concurency; ++th) {
        int seed = randomDevice();
        threads.push_back(std::thread([&img, &cam, &rend, th, seed, concurency, samples]() {
				std::mt19937 gen(seed);
				for (u32 i = th; i < img.x(); i += concurency) {
					if (th == 0) std::clog << "\rScanlines remaining: " << (img.x() - i) << ' ' << std::flush;
					for (u32 j = 0; j < img.y(); j++) {
						for (u8 sample = 0; sample < samples; sample++) {
							ray r = cam.get_ray(i, j, gen);
							img[i][j] += rend.ray_color(r, gen, 20);
						}
						img[i][j] /= samples;
						img[i][j] = renderer::gamma_correction(img[i][j]);
					}
				}
            }));
    }

    for (u32 th = 0; th < concurency; ++th) {
        threads[th].join();
    }

    std::clog << "\rDone.                 \n";


    image(img).to_png("out.png");
}