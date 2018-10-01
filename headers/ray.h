#ifndef RAY_H
#define RAY_H

#include "definitions.h"

//class Triangle;
//class Sphere;

class Ray{

private:
	Vertex startPoint;
	Vertex endPoint;

	ColorDbl rayColor;

	Triangle* collisionTriangle = nullptr;


public:
	Ray(Vertex& start, Vertex& end, ColorDbl c);
	void triangleHit(triangle* t, Vertex& pe);

	Vertex getStart() {return startPoint;}
	Vertex getEnd() {return endPoint;}

	ColorDbl getColor() { return rayColor; }
	Triangle* getTriangle() { return collisionTriangle; }


}



#endif