#include "surface.h"

Surface::Surface(const ColorDbl &color, const surfaceType st)
	:surfaceColor(color), type(st) {

}

ColorDbl Surface::getSurface() {
	
	if(type == diffuse){
		return surfaceColor*reflection;
	}
	else if (typ == specular) {
		return surfaceColor;
	}
	else { // if type == lightsource
		return ColorDbl(0, 0, 0);
	}
}