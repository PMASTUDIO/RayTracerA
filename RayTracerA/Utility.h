#pragma once
#include <random>

namespace Utility {
	inline float RandomFloat() {
		static std::uniform_real_distribution<float> distribution(0.0, 1.0);
		static std::mt19937 generator;
		return distribution(generator);
	}

	inline float Clamp(float x, float min, float max) {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}
}
