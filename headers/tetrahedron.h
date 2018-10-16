#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include "definitions.h"
#include "triangles.h"
#include "surface.h"

class Tetrahedron {
private:
	Vertex center;
	Vertex top, bot1, bot2, bot3;
	Triangle triangles[3];
	Surface tetrahedronSurface;
	float height;
	ColorDbl tetraColor;

public:
	Tetrahedron(Vertex c, float h, Surface s);
	bool rayIntersection(Ray &r);
	
}

#endif