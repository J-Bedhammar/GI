#ifndef CAMERA_H
#define CAMERA_H

#include "pixel.h"
#include "scene.h"
#include "ray.h"
#include "definitions.h"
#include <array>


class Camera {

private:
	Vertex eye1 = Vertex(0, 0, 0, 0);
	Vertex eye2 = Vertex(-2, 0, 0, 0);

	int whichEye = 1;

	static const int CAMERA_VIEW = 600;
	Pixel *pixels;

	ColorDbl castRay(Ray r, int num_reflections, Scene& scene, int percent);
	double randMinMax(const double& min, const double& max);

public:
	Camera(int i);
	~Camera() = default;
	void render(Scene& scene);
	void createImage();
	double subpixels = 5;
	double samples = 3;

	const int MAX_REFLECTIONS = 10;
	float maxColor = 0.0f;
	float minColor = 0.0f;
};

#endif
