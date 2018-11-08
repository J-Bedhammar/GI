#ifndef SURFACE_H
#define SURFACE_H

#include "Definitions.h"
#include "ray.h"

class Surface {

private:
	ColorDbl surfaceColor;
	float reflection = 0.95; //3/PI??
public:
	Surface();
	Surface(const ColorDbl &color, const surfaceType st);
	ColorDbl getSurfaceColor();

	surfaceType type;
};

#endif