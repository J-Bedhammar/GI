#include "lightsource.h"

Lightsource(Triangle t, Surface s)
	:lightTriangle(t), lightSurface(s) {

}

bool rayIntersect(Ray &r) {

	if (lightTriangle.rayIntersection(r))
		return true;
	else
		return false;
}