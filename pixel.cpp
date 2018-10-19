#include "pixel.h"

void Pixel::addRay(Ray* r) {
	intersectRays.push_back(r);
	pixelColor += r->getColor();
}