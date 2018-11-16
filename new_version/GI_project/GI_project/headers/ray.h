#ifndef RAY_H
#define RAY_H

#include "definitions.h"
#include <random>
//#include <cmath>

class Triangle;
class Sphere;

class Ray {

private:
	Vertex startPoint;
	Vertex endPoint;

	ColorDbl rayColor;

	Triangle* collisionTriangle = nullptr;
	Sphere* collisionSphere = nullptr;


public:
	~Ray() = default;
	Ray(Vertex &start, Vertex &end, ColorDbl c);

	void triangleHit(Triangle* t, Vertex &ip);
	void sphereHit(Sphere* s, Vertex &ip);

	Vertex getStart() { return startPoint; }
	Vertex getEnd() { return endPoint; }

	void setColor(ColorDbl color) { rayColor = color; }
	ColorDbl getColor() { return rayColor; }

	Triangle* getTriangle() { return collisionTriangle; }
	Sphere* getSphere() { return collisionSphere; }
	Direction getDirection() { return Direction(endPoint.x - startPoint.x, endPoint.y - startPoint.y, endPoint.z - startPoint.z); }

	Ray randHemisphere(glm::vec3 position, Direction normal, ColorDbl clr);


};


#endif