#ifndef CAMERA_H
#define CAMERA_H

#include "pixel.h"
#include "scene.h"
#include "ray.h"
#include "definitions.h"
#include <array>
//#include <fstream>
//castray

class Camera {

private:
	Vertex eye1 = Vertex(-1, 0, 0, 0);
	Vertex eye2 = Vertex(-2, 0, 0, 0);
	int whichEye = 1;

	static const int CAMERA_VIEW = 50;
	//std::array<std::array<Pixel, CAMERA_VIEW>, CAMERA_VIEW> pixels;
	Pixel *pixels;

	ColorDbl castRay(Ray& r, int num_reflections, Scene& scene);

public:
	Camera(int i);
	~Camera() = default;
	void render(Scene& scene);
	void createImage();

	const int MAX_REFLECTIONS = 5;
	float maxColor = 0.0;
};

#endif
