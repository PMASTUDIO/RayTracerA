#include "Ray.h"

Ray::Ray()
{

}

Ray::Ray(const glm::vec3& origin, const glm::vec3& direction) : orig(origin), dir(direction)
{

}

glm::vec3 Ray::GetTimePos(float t) const
{
	return orig + t * dir;
}

