#include "headers/surface.h"

//ADD BRDF, hemisphere shit

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
		glm::vec3 rayDirection = r.getEnd() - r.getStart();
		glm::vec3 newDirection = glm::reflect(rayDirection, normal);

		const float distance = 1000.0f;			// Check err when adding sphere - see Ray.cpp
		Vertex newEnd = Vertex(r.getEnd().x + (newDirection.x*distance), r.getEnd().y + (newDirection.y*distance), r.getEnd().z + (newDirection.z*distance), 0);

		Ray newRay = Ray(r.getEnd(), newEnd, getSurfaceColor());

		return newRay;
	}
	else {
		//Invalid reflection
		std::cout << "Invalid reflection" << std::endl;
	}
}
