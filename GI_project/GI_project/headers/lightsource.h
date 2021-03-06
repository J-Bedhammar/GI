#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "definitions.h"
#include "ray.h"
#include "triangle.h"


class Lightsource {
private:
	Triangle lightTriangle;
	Surface lightSurface;
	ColorDbl whiteLight{ 1, 1, 1 };
public:

	Lightsource(Triangle t);
	bool rayLightIntersection(Ray &r);
	Triangle getLightTriangle() { return lightTriangle; };
};


#endif