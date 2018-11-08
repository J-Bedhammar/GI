#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Definitions.h"
#include "ray.h"
#include "surface.h"
#include "glm/glm/glm.hpp"

class Triangle {

private:

	Vertex v0, v1, v2;
	Direction triangleNormal;
	Surface triangleSurface;

public:
	Triangle();
	Triangle(Vertex& a, Vertex& b, Vertex& c, Surface s);
	Direction getNormal() { return triangleNormal; }
	Surface getSurface() { return triangleSurface; }
	bool rayIntersection(Ray& r);

};

#endif