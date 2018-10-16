#include "surface.h"

Surface::Surface(const ColorDbl &color, const surfaceType st)
	:surfaceColor(color), type(st) {

}

ColorDbl Surface::getSurfaceColor() {
	
	if(type == diffuse){
		return surfaceColor*reflection;
	}
	else if (type == specular) {
		return surfaceColor;
	}
	else { // if type == lightsource
		return ColorDbl(0.0f, 0.0f, 0.0f);
	}
}