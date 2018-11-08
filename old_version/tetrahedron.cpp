#include "headers/tetrahedron.h"
#include "math.h"

Tetrahedron::Tetrahedron(Vertex c, float h, Surface s)
	: center(c), height(h), tetrahedronSurface(s)
{
	float S = height / sqrt(2 / 3);
	float L = sqrt(S*S - height*height);

	top = center + Vertex(0, height*(3 / 4), 0, 0);
	bot1 = center + Vertex(L, (-height / 4), 0, 0);
	bot2 = center + Vertex((-L / 2), (-height / 4), (sqrt(3) / 2)*L, 0);
	bot3 = center + Vertex((-L / 2), (-height / 4), (-sqrt(3) / 2)*L, 0);

	triangles[0] = Triangle(top, bot2, bot1, s);
	triangles[1] = Triangle(top, bot3, bot2, s);
	triangles[2] = Triangle(top, bot1, bot3, s);
	triangles[3] = Triangle(bot1, bot2, bot3, s);
}

bool Tetrahedron::rayIntersection(Ray &r) {

	if (triangles[0].rayIntersection(r) || triangles[1].rayIntersection(r) || triangles[2].rayIntersection(r) || triangles[3].rayIntersection(r))
		return true;
	else
		return false;
}