#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "definitions.h"
#include "surface.h"
#include "ray.h"

class Triangle {

private:
	Vertex v0, v1, v2;
	Direction triangleNormal;
	Surface triangleSurface;

public:
	Triangle();
	~Triangle() = default;
	Triangle(Vertex &a, Vertex &b, Vertex &c, Surface s);
	Direction getNormal() { return triangleNormal; }
	Surface getSurface() { return triangleSurface; }
	bool rayTriangleIntersection(Ray &r);

};

#endif

