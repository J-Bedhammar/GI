#include "ray.h"

ray::Ray(Vertex& start, Vertex& end, ColorDbl c) 
	: startPoint(start), endPoint(end), rayColor(c){

}

void ray::triangleHit(triangle* t, Vertex& pe) 
	:collisionTriangle(t), endPoint(pe){


}