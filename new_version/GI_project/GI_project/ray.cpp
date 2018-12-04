#include "headers/ray.h"
#include "gtx/rotate_vector.hpp"

Ray::Ray(Vertex &start, Vertex &end, ColorDbl c)
	: startPoint(start), endPoint(end), rayColor(c) {

}

void Ray::triangleHit(Triangle* t, Vertex& ip) {
	collisionTriangle = t;
	endPoint = ip;
	collisionSphere = nullptr;
};


void Ray::sphereHit(Sphere* s, Vertex& ip) {
	collisionSphere = s;
	endPoint = ip;
	collisionTriangle = nullptr;
};

Ray Ray::randHemisphere(glm::vec3 position, Direction normal, ColorDbl clr) {
	//randfunctions rand1 rand2
	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(0.0, 1.0);
	float randNum1 = distribution(generator);
	float randNum2 = distribution(generator);

	//create a tangent
	glm::vec3 helper = normal + glm::vec3(1, 1, 1);
	glm::vec3 tangent = glm::normalize(glm::cross(normal, helper));
	//azimuth and inclination  angles
	float inclination = acos(sqrt(randNum1));
	float azimuth = 2 * M_PI*randNum2;
	glm::vec3 newDirection = normal;

	//rotate around tangent
	newDirection = glm::normalize(glm::rotate(newDirection, inclination, tangent));
	//rotate around normal
	newDirection = glm::normalize(glm::rotate(newDirection, azimuth, normal));


	Vertex newStart = Vertex(position.x, position.y, position.z, 0);
	Vertex newEnd = Vertex(position.x + newDirection.x, position.y + newDirection.y, position.z + newDirection.z, 0);


	return Ray(newStart, newEnd, clr);

};