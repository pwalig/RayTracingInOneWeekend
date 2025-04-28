#include "renderer.hpp"
#include "ray.hpp"
#include "intersection_info.hpp"

glm::vec3 rt::renderer::ray_color(const ray& r, u32 depth)
{
	if (depth == 0) return glm::vec3(0.0f);

	intersection_info ii = r.cast(world);
	if (ii.hit()) {
		glm::vec3 attenuation;
		ray scattered;
		if (materials[ii.material].scatter(r, ii, gen, attenuation, scattered)) {
			return attenuation * ray_color(scattered, depth - 1);
		}
	}
	float a = 0.5*(r.dir.y + 1.0);
	return (1.0f-a)*glm::vec3(1.0f, 1.0f, 1.0f) + a*glm::vec3(0.5f, 0.7f, 1.0f);
}
