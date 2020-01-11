#include "headers/ray.h"
#include "gtx/rotate_vector.hpp"

Ray::Ray(Vertex start, Vertex end, ColorDbl c)
	: startPoint(start), endPoint(end), rayColor(c) {

	if ((start.x != start.x) || (end.x != end.x)) {}
		//std::cout << "Invalid input in Ray" << std::endl;
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

Ray Ray::randHemisphere(Ray& r, Direction normal, ColorDbl clr) {
	//position and direction
	glm::vec3 position = r.getEnd();
	glm::vec3 rayDirection = r.getEnd() - r.getStart();
	const float distance = 1000.0f;

	//rand numbers
	static std::default_random_engine generator;
	static std::uniform_real_distribution<float> distribution(0.0, 1.0);
	float randNum1 = distribution(generator);
	float randNum2 = distribution(generator);

	//create the axes - FÖ11
	auto v1 = glm::normalize(-rayDirection - glm::dot(-rayDirection, normal)*normal);
	auto v2 = glm::cross(-v1, normal);
	
	//azimuth and inclination angles
	float inclination = asin(sqrt(randNum2));
	float azimuth = 2* M_PI * randNum1; 
	glm::vec3 newDirection = normal;
	 
	//rotate around tangent
	newDirection = glm::normalize(glm::rotate(newDirection, inclination, v2));
	//rotate around normal
	newDirection = glm::normalize(glm::rotate(newDirection, azimuth, normal));

	Vertex newStart = Vertex(position.x, position.y, position.z, 1);
	Vertex newEnd = Vertex(position.x + (newDirection.x*distance), position.y + (newDirection.y*distance), position.z + (newDirection.z*distance), 1);

	return Ray(newStart, newEnd, clr);

};

Direction Ray::getDirection() {

	Direction dir = glm::normalize(Direction(endPoint.x - startPoint.x, endPoint.y - startPoint.y, endPoint.z - startPoint.z));

	return dir; 
}