#ifndef PIXEL_H
#define PIXEL_H

#include "definitions.h"
#include "ray.h"
#include <vector>

class Pixel {

private:
	ColorDbl pixelColor;
	std::vector<Ray*> pixelRays;

public:
	void addRay(Ray* r);
	ColorDbl getColor() { return pixelColor; }
};

#endif