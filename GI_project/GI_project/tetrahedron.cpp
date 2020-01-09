#include "headers/tetrahedron.h"
#include <cmath>
#include "gtx/rotate_vector.hpp"

Tetrahedron::Tetrahedron(Vertex c, float h, Surface s)
	: center(c), height(h), tetrahedronSurface(s)
{
	float S = height / sqrt(2.0 / 3.0);
	float L = sqrt(S*S - height*height);


	top = center + Vertex(0.0, 0.0, height*(3.0 / 4.0), 0.0);
	bot2 = center + Vertex(-L, 0.0, (-height / 4.0), 0.0);
	bot1 = center + Vertex((-L / 2.0), (sqrt(3.0) / 2.0)*L, (-height / 4.0), 0.0);
	bot3 = center + Vertex((-L / 2.0), (-sqrt(3.0) / 2.0)*L, (-height / 4.0),  0.0);

	tetraTriangles[0] = Triangle(top, bot1, bot2, s);
	tetraTriangles[1] = Triangle(top, bot2, bot3, s);
	tetraTriangles[2] = Triangle(top, bot3, bot1, s);
	tetraTriangles[3] = Triangle(bot1, bot3, bot2, s);
}

bool Tetrahedron::rayTetraIntersection(Ray &r) {

	if (tetraTriangles[0].rayTriangleIntersection(r) || tetraTriangles[1].rayTriangleIntersection(r) || tetraTriangles[2].rayTriangleIntersection(r) || tetraTriangles[3].rayTriangleIntersection(r))
		return true;
	else
		return false;
}