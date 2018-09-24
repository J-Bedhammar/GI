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

public:
	Triangle(Vertex& v0, Vertex& v1, Vertex& v2);
	Direction getNormal() { return triangleNormal; }
	bool rayIntersection(Ray& r);


}

#endif