#include "headers/surface.h"
#define M_PI 3.14159f
//ADD BRDF, hemisphere shit

Surface::Surface() {
	std::cout << "Fake surface!" << std::endl;
}


Surface::Surface(const ColorDbl &color, const surfaceType st)
	:surfaceColor(color), type(st) {
}


ColorDbl Surface::getSurfaceColor() {

	if (type == diffuse) {
		return surfaceColor*reflection/M_PI;
	}
	else if (type == specular) {
		return surfaceColor;
	}
	else { // if type == lightsource
		return ColorDbl(0.0f, 0.0f, 0.0f);
	}
}

//ADD BRDF

Ray Surface::reflectType( const Ray& r, const glm::vec3 &position, const Direction &normal ) {

	if (type == diffuse) {
		//hemisphere shit
	}
	else if (type == specular) {
		//glm::reflect shit
	}
	else {
		//Invalid reflection
	}

}
