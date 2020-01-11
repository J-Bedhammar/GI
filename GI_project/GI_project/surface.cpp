#include "headers/surface.h"
#include <cmath>

Surface::Surface() {
	//std::cout << "Fake surface!" << std::endl;
}


Surface::Surface(const ColorDbl &color, const std::string st)
	:surfaceColor(color), type(st) {
}


ColorDbl Surface::getSurfaceColor() {

	if (type ==  "diffuse") {
		return surfaceColor*reflection/M_PI;
	}
	else if (type == "specular") {
		return surfaceColor;
	}
	else { // if type == lightsource
		return ColorDbl(1.0f, 1.0f, 1.0f);
	}
}

//BRDF
Ray Surface::reflectType( Ray& r, const Direction &normal ) {

	if (type == "diffuse") {
		
		return r.randHemisphere(r, normal, getSurfaceColor());

	}
	else if (type == "specular") {

		glm::vec4 IP = glm::vec4(glm::vec3(r.getEnd()) + 0.001f * normal, 1);

		glm::vec3 rayDirection = normalize(glm::vec3(IP) - glm::vec3(r.getStart()));

		glm::vec3 newDirection = glm::vec4(glm::reflect(rayDirection, normal), 1);
		//Alternative to glm::reflect: I - 2(I*N)N
		//glm::vec3 newDirection = glm::normalize(rayDirection) - (2.0f * (glm::dot(glm::normalize(rayDirection), glm::normalize(normal)) * normal));

		const float distance = 1000.0f;	

		auto start = IP;

		Vertex newEnd = Vertex(newDirection.x, newDirection.y, newDirection.z, 1) * distance;
		Ray newRay = Ray(start, newEnd, getSurfaceColor());

		return newRay;
		
	}
	else {
		//Invalid reflection
		std::cout << "Invalid reflection" << std::endl;
	}
}
