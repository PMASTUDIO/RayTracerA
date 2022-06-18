#pragma once

#include "HittableObject.h"
#include <memory>
#include <vector>

class HittableObjectList : public HittableObject {
public:
	HittableObjectList(){}
	HittableObjectList(std::shared_ptr<HittableObject> object) { Add(object); }

	void Clear();
	void Add(std::shared_ptr<HittableObject> object);

	bool Hit(const Ray& r, HitEvent& rec, float t_min, float t_max) const override;

public:
	std::vector<std::shared_ptr<HittableObject>> objects;
};
