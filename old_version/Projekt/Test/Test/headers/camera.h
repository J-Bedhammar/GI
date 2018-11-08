#ifndef CAMERA_H
#define CAMERA_H

#include "pixel.h"
#include "scene.h"
#include "ray.h"
#include "Definitions.h"
#include <array>
#include <fstream>

class Camera {
	

	Vertex eye1 = Vertex(-1, 0, 0, 0);
	Vertex eye2 = Vertex(-2, 0, 0, 0);
	int whichEye = 1; //1 = eye1, 2 = eye2

	static const int CAMERA_VIEW = 800;
	std::array<std::array<Pixel, CAMERA_VIEW>, CAMERA_VIEW> pixels;

	ColorDbl castRay(Ray& r, int num_reflections, Scene& scene);

public:
	void render(Scene& scene);
	void createImage();

	const int MAX_REFLECTIONS = 10;
};

#endif