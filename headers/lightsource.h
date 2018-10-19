#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "Definitions.h"
#include "ray.h"
#include "triangle.h"


class Lightsource{
private:
	Triangle lightTriangle;
	Surface lightSurface;
	ColorDbl whiteLight{ 1, 1, 1 };
public:
	
	Lightsource(Triangle t);
	bool rayIntersection(Ray &r);
};


#endif