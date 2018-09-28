#ifndef CAMERA_H
#define CAMERA_H

#include "pixels.h"
#include "scene.h"
#include "ray.h"
#include "Definitions.h"
#include <array>

class camera() {

	Vertex eye1 = Vertex(-1, 0, 0, 0);
	Vertex eye2 = Vertex(-2, 0, 0, 0);
	int whichEye = 1; //1 = eye1, 2 = eye2

	const int CAMERA_VIEW = 800;
	std::array<std::array<pixel, CAMERA_VIEW>, CAMERA_VIEW> pixels;

public:
	void render();
}
#endif