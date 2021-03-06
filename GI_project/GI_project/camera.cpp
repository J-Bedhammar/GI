#include "headers/camera.h"
#include "gtx/vector_angle.hpp"
#include <stdio.h>
#include <errno.h>
#include <algorithm>


Camera::Camera(int i) {
	if (i == 1)
		whichEye = i;
	else if (i == 2)
		whichEye = i;
	else
		std::cout << "Wrong input (cameraPosition)" << std::endl;


	pixels = new Pixel[CAMERA_VIEW*CAMERA_VIEW];
}

void Camera::render(Scene& scene) {

	std::cout << "Rendering..." << std::endl;

	float delta = 2 / float(CAMERA_VIEW);

	//Loop through pixels
	for (int r = 0; r < CAMERA_VIEW; r++) {

		//Print percentage of how much the render function has completed
		double helper1 = r;
		double helper2 = CAMERA_VIEW;
		int percent = (helper1 / helper2) * 100;
		std::cout << percent << "%" << std::endl;

		for (int c = 0; c < CAMERA_VIEW; c++) {

			float fov = M_PI / 2;
			double pixelStep = 1.0 / subpixels;
			ColorDbl color = ColorDbl(0, 0, 0);

			for (int i = 0; i < samples; i++) { //Samples
				for (int subPy = 0; subPy < subpixels; ++subPy) {//Subpixels
					float Py = tan(fov / 2) * (1 - 2 * (randMinMax(c + (subPy * pixelStep), c + ((subPy + 1.0) * pixelStep))) / CAMERA_VIEW);

					for (int subPz = 0; subPz < subpixels; ++subPz) {
						float Pz = tan(fov / 2) * (2 * (randMinMax(r + (subPz * pixelStep), r + ((subPz + 1.0) * pixelStep))) / CAMERA_VIEW - 1);

						Vertex ps = eye1;

						// choose eye
						if (whichEye == 1)
							ps = eye1;
						if (whichEye == 2)
							ps = eye2;

						//end point	
						//Vertex pe = D + ps;
						Vertex pe = glm::vec4(1.0f, Py, -Pz, 1.0f) * 100.0f;

						// equation ray from eye to pixel(i,j), color: white
						Ray ray = Ray(ps, pe, ColorDbl(1, 1, 1));

						//rayIntersection
						color += castRay(ray, 1, scene, percent);

					}
				}
			}
			//Take average of subpixels and samples
			color /= (samples * subpixels * subpixels);

			pixels[c + r*CAMERA_VIEW].setColor(color);
		}
	}

	createImage();
}


ColorDbl Camera::castRay(Ray r, int num_reflections, Scene& scene, int percent) {

	ColorDbl pixelColor = ColorDbl(0.0, 0.0, 0.0);
	
	//Find first intersection point on a surface
	//what does it intersect with?
	scene.intersections(r);

	//Declare a surface and normal 
	Surface intersectedSurface;
	Direction normal;

	if (r.getTriangle()) { // intersects with triangle
		normal = r.getTriangle()->getNormal();
		intersectedSurface = r.getTriangle()->getSurface();
		//if triangle is a lightsource
		if (r.getTriangle()->getSurface().type == "lightsource") {
			return intersectedSurface.getSurfaceColor();
		}

		//Reflect, based on type
		Ray reflectedRay = intersectedSurface.reflectType(r, normal);

		//Emitted color
		double theta = glm::angle(reflectedRay.getDirection(), normal);
		ColorDbl emittedColor = intersectedSurface.getSurfaceColor();
		emittedColor = ColorDbl(emittedColor.x*abs(cos(theta)), emittedColor.y*abs(cos(theta)), emittedColor.z*abs(cos(theta)));
		
		//Shadowrays
		ColorDbl illumination = scene.sendShadowRays(r.getEnd(), intersectedSurface.getSurfaceColor(), normal);
		pixelColor += emittedColor;
		pixelColor *= illumination;

		//Russian roulette
		float threshold = 0.4;
		static std::default_random_engine generator;
		static std::uniform_real_distribution<float> distribution(0.0, 1.0);
		float randNum = distribution(generator);
		bool terminate = false;

		//May get terminated
		if (randNum < threshold) {
			
			//randomly terminate ray depending on its contribution
			float randNum2 = distribution(generator);
			float contribution = glm::max(glm::max(emittedColor.x, emittedColor.y), emittedColor.z);

			if (contribution < randNum2) {
				terminate = true;
			}
		}

		if (num_reflections < MAX_REFLECTIONS && !terminate) {
			int nextReflection = (intersectedSurface.type == "specular") ? num_reflections : (num_reflections + 1);
			//sends out the reflected ray, multiplied with the reflectioncoefficant 
			pixelColor += castRay(reflectedRay, nextReflection, scene, percent)*intersectedSurface.getReflection();
		}

	}
	else if(r.getSphere()){ //intersects with sphere
		normal = r.getSphere()->getNormal(r.getEnd());
		intersectedSurface = r.getSphere()->getSurface();

		//Reflect, based on type
		Ray reflectedRay = intersectedSurface.reflectType(r, normal);
		
		double theta = glm::angle(reflectedRay.getDirection(), normal);

		ColorDbl emittedColor = intersectedSurface.getSurfaceColor();
		emittedColor = ColorDbl(emittedColor.x*abs(cos(theta)), emittedColor.y*abs(cos(theta)), emittedColor.z*abs(cos(theta)));

		//Shadowrays
		ColorDbl illumination = scene.sendShadowRays(r.getEnd(), intersectedSurface.getSurfaceColor(), normal);
		pixelColor += emittedColor;
		pixelColor *= illumination;


		//Russian roulette
		float threshold = 0.4;
		static std::default_random_engine generator;
		static std::uniform_real_distribution<float> distribution(0.0, 1.0);
		float randNum = distribution(generator);
		bool terminate = false;

		//may get terminated
		if (randNum < threshold) {
			
			//randomly terminate ray depending on its contribution
			float randNum2 = distribution(generator);
			float contribution = glm::max(glm::max(emittedColor.x, emittedColor.y), emittedColor.z);

			if (contribution < randNum2) {
				terminate = true;
			}
		}

		if (num_reflections < MAX_REFLECTIONS && !terminate) {
			int nextReflection = (intersectedSurface.type == "specular") ? num_reflections : num_reflections + 1;
			//sends out the reflected ray, multiplied with the reflectioncoefficant 
			pixelColor += castRay(reflectedRay, nextReflection, scene, percent)*intersectedSurface.getReflection();
		}
	}
	else { //No intersection
		return pixelColor;
	}

	//find max rgb value
	maxColor = glm::max(maxColor, glm::max(pixelColor.x, glm::max(pixelColor.y, pixelColor.z)));
	minColor = glm::min(minColor, glm::min(pixelColor.x, glm::min(pixelColor.y, pixelColor.z)));

	return pixelColor;
}

void Camera::createImage() {

	std::cout << maxColor << std::endl;
	std::cout << minColor << ", After norm - " << double(minColor/maxColor) <<std::endl;
	std::string name = "RayTraceOutput.ppm";
	FILE *file;
	errno_t err = fopen_s(&file, name.c_str(), "wb");
	(void)fprintf(file, "P3\n%d %d\n255\n", CAMERA_VIEW, CAMERA_VIEW);
	for (int r = 0; r < CAMERA_VIEW; r++) {
		for (int c = 0; c < CAMERA_VIEW; c++) {
			ColorDbl color = pixels[c + r*CAMERA_VIEW].getColor();

			maxColor = 1;
			
			(void)fprintf(file, "%d %d %d ",
				(int)(255 * (color.x /maxColor)),
				(int)(255 * (color.y /maxColor)),
				(int)(255 * (color.z /maxColor))
			);
		}
	}
	fclose(file);
	std::cout << "Image is done!" << std::endl;
}

double Camera::randMinMax(const double& min, const double& max) {
	static std::default_random_engine generator;
	static std::uniform_real_distribution<float> distribution(0.0, 1.0);
	float rand = distribution(generator);

	return min + rand * (max - min);
}
