#pragma once

#include "HittableObject.h"

class Ray;

class Sphere : public HittableObject {
public:
	Sphere() {}
	Sphere(float r, glm::vec3& position) : radius(r), pos(position) {}

	bool Hit(const Ray& ray, HitEvent& rec, float t_min, float t_max) const override;

public:
	float radius;
	glm::vec3 pos;
};

