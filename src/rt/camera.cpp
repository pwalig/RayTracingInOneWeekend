#include "camera.hpp"

glm::vec3 random_in_unit_disk(float radius, rt::Rand& gen) {
	std::uniform_real_distribution<float> dist(-radius, radius);
	while (true) {
		glm::vec3 p = glm::vec3(dist(gen), dist(gen), 0.0f);
		if (glm::length(p) < radius)
			return p;
	}
}

glm::quat lookAt(
	const glm::vec3& source,
	const glm::vec3& dest,
	const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
	const glm::vec3& forward = glm::vec3(0.0f, 0.0f, 1.0f)
) {
	glm::vec3 dir = glm::normalize(dest - source);

	glm::vec3 nonUpDir = glm::normalize(dir - (glm::dot(dir, up) * up));
	float upAngle = glm::acos(glm::dot(forward, nonUpDir));
	glm::vec3 upAxis = glm::cross(forward, nonUpDir);
	glm::quat aroundUp = glm::angleAxis(upAngle, glm::dot(upAxis, upAxis) > 0.0f ? glm::normalize(upAxis) : up);

	glm::vec3 side = glm::normalize(glm::cross(up, forward));
	glm::vec3 nonAxisDir = glm::normalize(dir - (glm::dot(dir, side) * side));
	float axisAngle = glm::acos(glm::dot(forward, nonAxisDir));
	glm::vec3 axis = glm::cross(forward, nonAxisDir);
	glm::quat aroundAxis = glm::angleAxis(axisAngle,
		aroundUp * (glm::dot(axis, axis) > 0.0f ? glm::normalize(axis) : side)
	);

	return aroundAxis * aroundUp;
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

	rot = ::lookAt(Position, lookAt, glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
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
