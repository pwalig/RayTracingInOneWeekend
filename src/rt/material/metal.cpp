#include "metal.hpp"

#include "../ray.hpp"
#include "../intersection_info.hpp"

bool rt::metal::scatter(const ray& r_in, const intersection_info& rec, const material& mat, Rand& gen, glm::vec3& attenuation, ray& scattered)
{
	glm::vec3 reflected = glm::reflect(r_in.dir, rec.normal);
	reflected = glm::normalize(reflected + (mat.fuzz * random_vector(gen)));
	scattered = ray(rec.point, reflected);
	attenuation = mat.albedo;
	//return true;
	return (glm::dot(scattered.dir, rec.normal) > 0);
}
