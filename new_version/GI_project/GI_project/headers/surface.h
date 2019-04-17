#ifndef SURFACE_H
#define SURFACE_H

#include "definitions.h"
#include "ray.h"

class Surface {

private:
	ColorDbl surfaceColor;
	float reflection = 0.4f;

public:
	Surface();
	~Surface() = default;
	Surface(const ColorDbl &color, const std::string st);
	ColorDbl getSurfaceColor();
	Ray reflectType(Ray& r, const Direction &normal);
	float getReflection() { return reflection; };

	std::string type = "diffuse";

};

#endif