#include "HittableObjectList.h"



void HittableObjectList::Clear()
{
	objects.clear();
}

void HittableObjectList::Add(std::shared_ptr<HittableObject> object)
{
	objects.push_back(object);
}

bool HittableObjectList::Hit(const Ray& r, HitEvent& rec, float t_min, float t_max) const
{
	HitEvent evt;
	bool has_hit = false;
	float closest_hit = t_max;

	for (const auto& object : objects) {
		if (object->Hit(r, evt, t_min, closest_hit)) {
			has_hit = true;
			closest_hit = evt.t;
			rec = evt;
		}
	}

	return has_hit;
}
