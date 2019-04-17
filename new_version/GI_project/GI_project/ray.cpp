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

Ray Ray::randHemisphere(Ray r, Direction normal, ColorDbl clr) {

	//randfunctions rand1 rand2
	//std::cout << "\nnormal " << normal.x << "," << normal.y << "," << normal.z << std::endl;
	glm::vec3 position = r.getEnd();
	glm::vec3 rayDirection = glm::vec3(r.getEnd().x - r.getStart().x, r.getEnd().y - r.getStart().y, r.getEnd().z - r.getStart().z);
	
	//std::cout << "rayDirection: " << rayDirection.x << "," << rayDirection.y << "," << rayDirection.z << std::endl;

	static std::default_random_engine generator;
	static std::uniform_real_distribution<float> distribution(0.0, 1.0);
	float randNum1 = distribution(generator);
	float randNum2 = distribution(generator);

	normal = normal + glm::vec3(1, 1, 1);
	//create the axes - FÖ11
	//glm::vec3 helper = rayDirection;
	//glm::vec3 tangent = glm::normalize(glm::cross(normal, helper));
	auto v1 = glm::normalize(-position - glm::dot(-position, normal)*normal);
	auto v2 = -glm::cross(v1, normal);
	
	//azimuth and inclination angles
	float inclination = asin(sqrt(randNum2));
	//std::cout << "inclination: " << inclination << std::endl;
	float azimuth = 2* M_PI * randNum1; 
	//std::cout << "azimuth: " << azimuth << std::endl;
	glm::vec3 newDirection = normal;
	 
	//rotate around tangent
	newDirection = glm::normalize(glm::rotate(newDirection, inclination, v1));
	//rotate around normal
	newDirection = glm::normalize(glm::rotate(newDirection, azimuth, normal));

	Vertex newStart = Vertex(position.x, position.y, position.z, 1);

	Vertex newEnd = Vertex(newDirection.x, newDirection.y, newDirection.z, 1) *100.0f;

	newEnd = Vertex(newEnd.x + newStart.x, newEnd.y + newStart.y, newEnd.z + newStart.z, 1);

	//std::cout << "newDirection: " << newDirection.x << "," << newDirection.y << "," << newDirection.z << std::endl;
	//std::cout << "start: " << newStart.x << "," << newStart.y << "," << newStart.z << std::endl;
	//std::cout << "end: " << newEnd.x << "," << newEnd.y << "," << newEnd.z << std::endl;

	return Ray(newStart, newEnd, clr);

};

Direction Ray::getDirection() {

	Direction dir = glm::normalize(Direction(endPoint.x - startPoint.x, endPoint.y - startPoint.y, endPoint.z - startPoint.z));

	return dir; 
}