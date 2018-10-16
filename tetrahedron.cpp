#include "tetrahedron.h"
#include "math.h"

Tetrahedron::Tetrahedron(Vertex c, float h, Surface s)
	: Center(c), height(h), tetrahedronSurface(s)
{
	float S = height / sqrt(2 / 3);
	float L = sqrt(S*S - height*height);

	tetraColor = s.getSurfaceColor()

	top = Center + Vertex(0, height*(3 / 4), 0);
	bot1 = Center + Vertex(L, (-height / 4), 0);
	bot2 = Center + Vertex((-L / 2), (-height / 4), (sqrt(3) / 2)*L);
	bot3 = Center + Vertex((-L / 2), (-height / 4), (-sqrt(3) / 2)*L);

	triangles[0] = Triangle(top, bot2, bot1, tetraColor);
	triangles[1] = Triangle(top, bot3, bot2, tetraColor);
	triangles[2] = Triangle(top, bot1, bot3, tetraColor);
	triangles[3] = Triangle(bot1, bot2, bot3, tetraColor);
}

bool Tetrahedron::rayIntersection(Ray &r) {

	if (triangles[0].rayIntersection(r) || triangles[1].rayIntersection(r) || triangles[2].rayIntersection(r) || triangles[3].rayIntersection(r))
		return true;
	else
		return false;
}