#pragma once

#include "Ray.h"

#include <glm/glm.hpp>

struct HitEvent {
	glm::vec3 p;
	glm::vec3 normal;
	float t;
	bool front_face;

	inline void SetFaceNormal(const Ray& ray, const glm::vec3& outwardNormal) {
		front_face = glm::dot(ray.dir, outwardNormal) < 0;
		normal = front_face ? outwardNormal : -outwardNormal;
	}
};


class HittableObject {
public:
	virtual bool Hit(const Ray& r, HitEvent& rec, float t_min, float t_max) const = 0;
};
