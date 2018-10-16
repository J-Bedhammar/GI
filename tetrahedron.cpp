#include "tetrahedron.h"
#include "math.h"

Tetradron::Tetrahedron(Vertex c, int h, Surface s)
	: Center(c), height(h), tetrahedronSurface(s)
{
	float S = height / sqrt(2 / 3);
	float L = sqrt(S*S - height*height);

	top = Center + Vertex(0, height*(3 / 4), 0);
	bot1 = Center + Vertex(L, (-height / 4), 0);
	bot2 = Center + Vertex((-L / 2), (-height / 4), (sqrt(3) / 2)*L);
	bot3 = Center + Vertex((-L / 2), (-height / 4), (-sqrt(3) / 2)*L);


}