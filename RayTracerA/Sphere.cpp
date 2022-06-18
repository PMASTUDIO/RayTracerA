#include "Sphere.h"

#include "Ray.h"

#include <glm/glm.hpp>

bool Sphere::Hit(const Ray& ray, HitEvent& rec, float t_min, float t_max) const
{
	glm::vec3 oc = ray.orig - pos;
	float a_coef = glm::dot(ray.dir, ray.dir);
	float b_coef = 2 * glm::dot(ray.dir, oc);
	float c_coef = glm::dot(oc, oc) - pow(radius, 2);

	float delta = pow(b_coef, 2) - 4 * a_coef * c_coef;

	if (delta < 0) {
		// No collision
		return false;
	}
	
	float root = (-b_coef - sqrt(delta)) / (2 * a_coef); // root 1
	if (root < t_min || root > t_max) {
		root = (-b_coef + sqrt(delta)) / (2 * a_coef); // root 2
		if (root < t_min || root > t_max)
			return false;
	}
	
	rec.t = root;
	rec.p = ray.GetTimePos(rec.t);
	glm::vec3 outward_normal = (rec.p - pos) / radius;
	rec.SetFaceNormal(ray, outward_normal);

	return true;
	
}
