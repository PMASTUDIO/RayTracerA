#include "Camera.h"

#include "Ray.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/ext.hpp"

Camera::Camera(int viewportWidth, int viewportHeight)
{
	float aspect_ratio = (float)viewportWidth / viewportHeight;
	float viewport_height = 2.0;
	float viewport_width = viewport_height * aspect_ratio;
	float focal_length = 1.0;

	m_Origin = glm::vec3(0, 0, 0);
	Horizontal = glm::vec3(viewport_width, 0, 0);
	Vertical = glm::vec3(0, viewport_height, 0);
	m_LowerLeftCorner = m_Origin - Horizontal / 2 - Vertical / 2 - glm::vec3(0, 0, focal_length);
}

Ray Camera::GetRay(float u, float v) const
{
	return Ray(m_Origin, m_LowerLeftCorner + u * Horizontal + v * Vertical - m_Origin);
}
