#ifndef SURFACE_H
#define SURFACE_H

#include "definitions.h"
#include "ray.h"

class Surface {

private:
	ColorDbl surfaceColor;
	float reflection = 0.95; //3/PI??
public:
	Surface(const ColorDbl &color, const surfaceType st);
	ColorDbl getSurface();

	surfaceType type;
}

#endif