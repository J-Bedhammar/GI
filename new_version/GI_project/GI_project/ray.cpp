#include "headers/ray.h"
#include "gtx/rotate_vector.hpp"

Ray::Ray(Vertex start, Vertex end, ColorDbl c)
	: startPoint(start), endPoint(end), rayColor(c) {

	if ((start.x != start.x) || (end.x != end.x))
		std::cout << "Invalid input in Ray" << std::endl;

}

void Ray::triangleHit(Triangle* t, Vertex ip) {
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

	//create the axes - FÖ11
	auto v1 = glm::normalize(-position - glm::dot(-position, normal)*normal);
	auto v2 = -glm::cross(v1, normal);
	
	//azimuth and inclination angles
	float inclination = asin(sqrt(randNum2));
	float azimuth = inclination; // CORRECT: 2 * M_PI * randNum1 BUT IT DOESNT WORK
	glm::vec3 newDirection = normal;

	//rotate around tangent
	newDirection = glm::normalize(glm::rotate(newDirection, inclination, v2));
	//rotate around normal
	newDirection = glm::normalize(glm::rotate(newDirection, azimuth, normal));

	Vertex newStart = Vertex(position.x, position.y, position.z, 1);
	Vertex newEnd = Vertex(position.x + newDirection.x, position.y + newDirection.y, position.z + newDirection.z, 1);

	return Ray(newStart, newEnd, clr);

};

Direction Ray::getDirection() {

	Direction dir = glm::normalize(Direction(endPoint.x - startPoint.x, endPoint.y - startPoint.y, endPoint.z - startPoint.z));

	return dir; 
}