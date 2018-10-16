#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include "definitions.h"
#include "triangles.h"

class Tetrahedron {
private:
	Vertex center;
	Vertex top, bot1, bot2, bot3;
	Triangle triangles[3];
	Surface tetrahedronSurface;
	int height;

public:
	Tetrahedron(Vertex c, int h, Surface s);
	bool rayIntersection(Ray &r);
	
}

#endif