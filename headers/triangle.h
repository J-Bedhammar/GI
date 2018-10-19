#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "definitions.h"
#include "ray.h"
#include "glm/glm.hpp"

class Triangle() {

private:

	Vertex v0, v1, v2;
	ColorDbl triangleColor;
	Direction triangleNormal;
	Surface triangleSurface;

public:
	Triangle(Vertex& a, Vertex& b, Vertex& c, ColorDbl& color, Surface s);
	Direction getNormal() { return triangleNormal; }
	Surface getSurface() { return truangleSurface; }
	bool rayIntersection(Ray& r);



}

#endif