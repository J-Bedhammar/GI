#include "headers/pixel.h"

void Pixel::addRay(Ray* r) {
	pixelRays.push_back(r);
	pixelColor += r->getColor();
}