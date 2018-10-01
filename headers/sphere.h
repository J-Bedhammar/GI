#ifndef SPHERE_H
#define SPHERE_H

#include "ray.h"
#include "Definitions.h"

//ADD SURFACE?

class Sphere() {

private:
	float radius;
	Vertex center;
public:
	Sphere(float r, Vertex c )
	
	Vertex getCenter() { return center; }
	float getRadius() { return radius; }
	std::vec3 getNormal() { Vertex c}

}

#endif