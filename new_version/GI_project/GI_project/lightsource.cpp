#include "headers/lightsource.h"

Lightsource::Lightsource(Triangle t)
	:lightTriangle(t), lightSurface(t.getSurface()) {

}

bool Lightsource::rayLightIntersection(Ray &r) {

	if (lightTriangle.rayTriangleIntersection(r))
		return true;
	else
		return false;
}