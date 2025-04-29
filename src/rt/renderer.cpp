#include "renderer.hpp"
#include "ray.hpp"
#include "hit_info.hpp"

glm::vec3 rt::renderer::ray_color(ray& r, Rand& gen, u32 depth)
{
	if (depth == 0) return glm::vec3(0.0f);

	hit_info ii = r.cast(world);
	if (ii.hit()) {
		glm::vec3 attenuation;
		if (materials[ii.material].scatter(r, ii, gen, attenuation)) {
			return attenuation * ray_color(r, gen, depth - 1);
		}
		else return glm::vec3(0.0f, 0.0f, 0.0f);
	}
	float a = 0.5*(r.dir.y + 1.0);
	return (1.0f-a)*glm::vec3(1.0f, 1.0f, 1.0f) + a*glm::vec3(0.5f, 0.7f, 1.0f);
}
