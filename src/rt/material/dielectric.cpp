#include "dielectric.hpp"

#include "../ray.hpp"
#include "../intersection_info.hpp"

double reflectance(float cosine, float refraction_index) {
	// Use Schlick's approximation for reflectance.
	auto r0 = (1 - refraction_index) / (1 + refraction_index);
	r0 = r0*r0;
	return r0 + (1-r0)*std::pow((1 - cosine),5);
}

bool rt::dielectric::scatter(const ray& r_in, const intersection_info& rec, const material& mat, Rand& gen, glm::vec3& attenuation, ray& scattered)
{
	attenuation = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 norm = -rec.normal;
	float ri = mat.fuzz;
	if (glm::dot(rec.normal, r_in.dir) < 0.0f) {
		ri = 1.0f / mat.fuzz;
		norm = rec.normal;
	}
	float cos_theta = std::fmin(glm::dot(-r_in.dir, norm), 1.0f);
	float sin_theta = std::sqrt(1.0f - cos_theta * cos_theta);
	
	glm::vec3 dir;

	std::uniform_real_distribution<float>distrib(0.0f, 1.0f);
	if (ri * sin_theta > 1.0f || reflectance(cos_theta, ri) > distrib(gen)) {
		dir = glm::reflect(r_in.dir, norm);
	}
	else {
		dir = glm::refract(r_in.dir, norm, ri);
	}

	scattered = ray(rec.point, dir);
	return true;
}
