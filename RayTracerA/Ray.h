#pragma once

#include <glm/glm.hpp>

class Ray {
public:
	Ray();
	Ray(const glm::vec3& origin, const glm::vec3& direction);

	glm::vec3 GetTimePos(float t) const;

	glm::vec3 ray;
	glm::vec3 orig, dir;
	float t = 0;
};
