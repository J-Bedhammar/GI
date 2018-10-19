#include "headers/lightsource.h"

Lightsource::Lightsource(Triangle t)
	:lightTriangle(t), lightSurface(t.getSurface()) {

}

bool Lightsource::rayIntersection(Ray &r) {

	if (lightTriangle.rayIntersection(r))
		return true;
	else
		return false;
}