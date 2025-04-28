#include <iostream>

#include "rt/image.hpp"
#include "rt/ray.hpp"
#include "rt/camera.hpp"

using namespace rt;

int main() {

    image img(300, 200);
    camera cam(glm::vec3(0.0f), img.width, img.height, 1.0f, 2.0f);


    glm::vec3 pixel0 = cam.pixel0();
    //std::cout << pixel0.x << ' ' << pixel0.y << ' ' << pixel0.z << '\n';

	for (u32 i = 0; i < img.width; i++) {
		for (u32 j = 0; j < img.height; j++) {
            glm::vec3 pixelCenter = pixel0 + glm::vec3(i * cam.delta.x, j * cam.delta.y, 0.0f);
            glm::vec3 rayDir = pixelCenter - cam.pos;
            ray r(cam.pos, glm::normalize(rayDir));
			//std::cout << rayDir.x << ' ' << rayDir.y << ' ' << rayDir.z << '\n';
            img.at(i, j) = pixel(r.color());
            //img.at(i, j) = pixel(glm::vec3((float)(i) / img.width, float(j) / img.height, 0.0f));
        }
    }

    img.to_png("out.png");
}