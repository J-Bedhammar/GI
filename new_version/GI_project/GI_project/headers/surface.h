#ifndef SURFACE_H
#define SURFACE_H

#include "definitions.h"
#include "ray.h"

class Surface {

private:
	ColorDbl surfaceColor;
	float reflection = 0.85f;

public:
	Surface();
	~Surface() = default;
	Surface(const ColorDbl &color, const surfaceType st);
	ColorDbl getSurfaceColor();
	Ray reflectType(const Ray& r, const glm::vec3 &position, const Direction &normal);

	surfaceType type;
};

#endif