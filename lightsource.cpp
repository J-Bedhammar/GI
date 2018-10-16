#include "lightsource.h"

Lightsource::Lightsource(Triangle t, Surface s)
	:lightTriangle(t), lightSurface(s) {

}

bool Lightsource::rayIntersection(Ray &r) {

	if (lightTriangle.rayIntersection(r))
		return true;
	else
		return false;
}