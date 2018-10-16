#include "ray.h"

Ray::Ray(Vertex& start, Vertex& end, ColorDbl c) 
	: startPoint(start), endPoint(end), rayColor(c){

}

void Ray::triangleHit(triangle* t, Vertex& ip) 
	:collisionTriangle(t), endPoint(ip), collisionSphere(nullptr){
}


void Ray::sphereHit(sphere* s, Vertex& ip)
	:collisionSphere(s), endPoint(ip), collisionTriangle(nullptr){
}