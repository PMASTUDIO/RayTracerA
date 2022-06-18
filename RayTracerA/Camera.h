#pragma once

#include <glm/glm.hpp>
#include "Ray.h"

class Camera {
public:
	Camera(int viewportWidth, int viewportHeight);
	Ray GetRay(float u, float v) const;
private:
	glm::vec3 m_Origin;
	glm::vec3 m_LowerLeftCorner;
	glm::vec3 Horizontal;
	glm::vec3 Vertical;
};
