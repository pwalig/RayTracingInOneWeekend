#include "dielectric.hpp"

#include "../ray.hpp"
#include "../hit_info.hpp"

double reflectance(float cosine, float refraction_index) {
	// Use Schlick's approximation for reflectance.
	auto r0 = (1 - refraction_index) / (1 + refraction_index);
	r0 = r0*r0;
	return r0 + (1-r0)*std::pow((1 - cosine),5);
}

bool rt::dielectric::scatter(
	ray& r,
	const hit_info& rec,
	const material& mat,
	Rand& gen,
	glm::vec3& attenuation
) {
	attenuation = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 norm = rec.normal;
	float ri = r.exiting ? mat.fuzz : 1.0f / mat.fuzz;
	float cos_theta = std::fmin(glm::dot(-r.dir, norm), 1.0f);
	float sin_theta = std::sqrt(1.0f - cos_theta * cos_theta);
	
	glm::vec3 dir;

	std::uniform_real_distribution<float>distrib(0.0f, 1.0f);
	bool reflects = ri * sin_theta > 1.0f || reflectance(cos_theta, ri) > distrib(gen);
	if (reflects) {
		dir = glm::reflect(r.dir, norm);
	}
	else {
		dir = glm::refract(r.dir, norm, ri);
	}

	r = ray(rec.point, dir, reflects ? r.exiting : !r.exiting);
	return true;
}
