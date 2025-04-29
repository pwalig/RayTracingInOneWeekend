#include "metal.hpp"

#include "../ray.hpp"
#include "../intersection_info.hpp"

inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n) {
    return v - 2*glm::dot(v,n)*n;
}

bool rt::metal::scatter(const ray& r_in, const intersection_info& rec, const material& mat, Rand& gen, glm::vec3& attenuation, ray& scattered)
{
	glm::vec3 reflected = reflect(r_in.dir, rec.normal);
	scattered = ray(rec.point, reflected);
	attenuation = mat.albedo;
	return true;
}
