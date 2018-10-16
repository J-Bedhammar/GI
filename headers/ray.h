#ifndef RAY_H
#define RAY_H

#include "definitions.h"

class Triangle;
class Sphere;

class Ray{

private:
	Vertex startPoint;
	Vertex endPoint;

	ColorDbl rayColor;

	Triangle* collisionTriangle = nullptr;
	Sphere* collisionSphere = nullptr;


public:
	Ray(Vertex& start, Vertex& end, ColorDbl c);
	void triangleHit(triangle* t, Vertex& ip);
	void sphereHit(sphere* s, Vertex& ip);

	Vertex getStart() {return startPoint;}
	Vertex getEnd() {return endPoint;}

	ColorDbl getColor() { return rayColor; }
	Triangle* getTriangle() { return collisionTriangle; }
	Sphere* getSphere() { return collisionSphere; }

}



#endif