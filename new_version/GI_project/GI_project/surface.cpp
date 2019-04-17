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
		return ColorDbl(0.0f, 0.0f, 0.0f);
	}
}

//BRDF
Ray Surface::reflectType( Ray& r, const Direction &normal ) {

	if (type == "diffuse") {
		
		return r.randHemisphere(r, normal, getSurfaceColor());

	}
	else if (type == "specular") {
		glm::vec3 newDirection = glm::reflect(r.getDirection(), normal);

		Vertex newEnd = Vertex(newDirection.x + r.getStart().x, newDirection.y + r.getStart().y, newDirection.z + r.getStart().z, 0)*100.0f;

		Ray newRay = Ray(r.getStart(), newEnd, getSurfaceColor());

		return newRay;
	}
	else {
		//Invalid reflection
		std::cout << "Invalid reflection" << std::endl;
	}
}
