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
	Vertex eye1 = Vertex(0, 0, 0, 0);
	Vertex eye2 = Vertex(-2, 0, 0, 0);
	glm::vec4 cameraplane[4];

	glm::vec4 pixelplane[4]; 
	glm::vec4 planeWidthAxis;
	glm::vec4 planeHeigthAxis;

	float pixelStep;
	glm::vec4 wAxis;
	glm::vec4 hAxis;
	int whichEye = 1;

	static const int CAMERA_VIEW = 100;
	//std::array<std::array<Pixel, CAMERA_VIEW>, CAMERA_VIEW> pixels;
	Pixel *pixels;

	ColorDbl castRay(Ray r, int num_reflections, Scene& scene, int percent);

public:
	Camera(int i);
	~Camera() = default;
	void render(Scene& scene);
	void createImage();
	Ray* pixeltoray2(int w, int h);

	const int MAX_REFLECTIONS = 5;
	float maxColor = 0.0;
};

#endif
