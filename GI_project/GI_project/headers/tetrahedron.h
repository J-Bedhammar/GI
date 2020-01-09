#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H
#include "definitions.h"
#include "triangle.h"
#include "surface.h"

class Tetrahedron {
private:
	Vertex center;
	Vertex top, bot1, bot2, bot3;
	Triangle tetraTriangles[4];
	Surface tetrahedronSurface;
	float height;
	ColorDbl tetraColor;

public:
	Tetrahedron(Vertex c, float h, Surface s);
	bool rayTetraIntersection(Ray &r);
	Surface getSurface() { return tetrahedronSurface; }

};

#endif
