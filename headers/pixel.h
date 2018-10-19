#ifndef PIXEL_H
#define PIXEL_H

#include "Definitions.h"
#include "ray.h"
#include <vector>

class Pixel {
	
private:
	ColorDbl pixelColor;
	std::vector<Ray*> intersectRays;

public:
	void addRay(Ray* r);
	ColorDbl getColor() { return pixelColor; }
};

#endif