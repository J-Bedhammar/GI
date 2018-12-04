#ifndef PIXEL_H
#define PIXEL_H

#include "definitions.h"
#include "ray.h"
#include <vector>

class Pixel {

private:
	ColorDbl pixelColor;
	std::vector<Ray*> pixelRays;
	ColorDbl first;
	ColorDbl last;

public:
	Pixel() {};
	Pixel(ColorDbl c1, ColorDbl c2) {};
	~Pixel() = default;
	void addRay(Ray* r);
	ColorDbl getColor() { return pixelColor; }
	void setColor(ColorDbl newColor) { pixelColor = newColor; };
};

#endif