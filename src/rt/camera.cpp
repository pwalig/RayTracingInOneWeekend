#include "camera.hpp"

glm::vec3 random_in_unit_disk(float radius, rt::Rand& gen) {
	std::uniform_real_distribution<float> dist(-radius, radius);
	while (true) {
		glm::vec3 p = glm::vec3(dist(gen), dist(gen), 0.0f);
		if (glm::length(p) < radius)
			return p;
	}
}

rt::camera::camera(
	glm::vec3 Position, glm::vec3 lookAt,
	u32 width, u32 height,
	float fov, float focal, float blur
) :
	pos(Position), rot(),
	viewport(), offset(),
	delta(), defocus(focal * std::tan(glm::radians(blur / 2.0f)))
{
	viewport.y = 2.0f * focal * std::tan(glm::radians(fov) / 2.0f);
	viewport.x = viewport.y * float(width) / float(height);

	offset = glm::vec3(viewport.x / 2.0f, viewport.y / 2.0f, focal);
	delta = glm::vec2(-viewport.x / width, -viewport.y / height);

	glm::vec3 look = glm::normalize(lookAt - pos);
	glm::vec3 lookx = glm::normalize(glm::vec3(look.x, 0.0f, look.z));
	glm::vec3 looky = glm::normalize(glm::vec3(0.0f, look.y, look.z));
	//glm::vec3 cross = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), look);
	//rot.x = cross.x;
	//rot.y = cross.y;
	//rot.z = cross.z;
	//rot.w = glm::length(look) + glm::dot(glm::vec3(0.0f, 0.0f, 1.0f), look);
	//rot = glm::normalize(rot);

	rot = glm::quat(glm::vec3(
		glm::radians(8.588f),
		//glm::acos(glm::dot(looky, glm::vec3(0.0f, 0.0f, 1.0f))),
		glm::acos(glm::dot(lookx, glm::vec3(0.0f, 0.0f, 1.0f))),
		0.0f
	));
}

rt::ray rt::camera::get_ray(u32 x, u32 y, Rand& gen) const
{
	std::uniform_real_distribution<float> xdist(0.0f, 1.0f);
	glm::vec2 coord(xdist(gen) + x, xdist(gen) + y);
	glm::vec3 pixelCenter = offset + glm::vec3(coord.x * delta.x, coord.y * delta.y, 0.0f);
	glm::vec3 origin = glm::vec3(0.0f);
	if (defocus > 0.0f) origin = (random_in_unit_disk(defocus, gen));
	glm::vec3 rayDir = rot * (pixelCenter - origin);
	return ray(pos + (rot * origin), glm::normalize(rayDir));
}
