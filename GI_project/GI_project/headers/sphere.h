#ifndef SPHERE_H
#define SPHERE_H

#include "definitions.h"
#include "ray.h"
#include "surface.h"


class Sphere {

private:
	float radius;
	Vertex center;
	Surface sphereSurface;

public:
	Sphere(float r, Vertex c, Surface s);
	~Sphere() = default;

	Vertex getCenter() { return center; }
	float getRadius() { return radius; }
	Surface getSurface() { return sphereSurface; }
	bool raySphereIntersection(Ray& r);
	glm::vec3 getNormal(Vertex p);

};


#endif 