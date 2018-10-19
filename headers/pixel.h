#ifndef PIXEL_H
#define PIXEL_H

#include "definitions.h"
#include "ray.h"

class Pixel() {
	
private:
	ColorDbl pixelColor;
	std::vector<Ray> intersectRays
public:
	void addRay(Ray* r);
	ColorDbl getColor() { return pixelColor; }
};

#endif