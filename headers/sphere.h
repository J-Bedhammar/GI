#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"
#include "Definitions.h"
#include "surface.h"
#include "glm/glm.hpp"

//ADD SURFACE?

class Sphere() {

private:
	float radius;
	Vertex center;
	Surface sphereSurface;

public:
	Sphere(float r, Vertex c , Surface s);
	
	Vertex getCenter() { return center; }
	float getRadius() { return radius; }
	Surface getSurface() {return sphereSurface; }
	bool rayIntersection(Ray& r);
	glm::vec3 getNormal(Vertex c);

}

#endif