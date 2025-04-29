#include "metal.hpp"

#include "../ray.hpp"
#include "../hit_info.hpp"

bool rt::metal::scatter(ray& r, const hit_info& rec, const material& mat, Rand& gen, glm::vec3& attenuation)
{
	glm::vec3 reflected = glm::reflect(r.dir, rec.normal);
	reflected = glm::normalize(reflected + (mat.fuzz * random_vector(gen)));
	r = ray(rec.point, reflected, r.exiting);
	attenuation = mat.albedo;
	return (glm::dot(r.dir, rec.normal) > 0);
}
