#include "headers/camera.h"
#include "gtx/vector_angle.hpp"
#include <stdio.h>
#include <errno.h>
//CASTRAY
Camera::Camera(int i) {
	if (i == 1)
		whichEye = i;
	else if (i == 2)
		whichEye = i;
	else
		std::cout << "Wrong input (cameraPosition)" << std::endl;

	//JULLES KOD
	pixelplane[0] = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
	pixelplane[1] = glm::vec4(0.0f, -1.0f, 1.0f, 1.0f);
	pixelplane[2] = glm::vec4(0.0f, 1.0f, -1.0f, 1.0f);
	pixelplane[3] = glm::vec4(0.0f, -1.0f, -1.0f, 1.0f);
	planeWidthAxis = (pixelplane[1] - pixelplane[0]);
	planeHeigthAxis = (pixelplane[2] - pixelplane[0]);

	pixelStep = glm::length(planeHeigthAxis) / CAMERA_VIEW;

	planeWidthAxis = glm::normalize(planeWidthAxis);
	planeHeigthAxis = glm::normalize(planeHeigthAxis);

	pixels = new Pixel[CAMERA_VIEW*CAMERA_VIEW];
}

void Camera::render(Scene& scene) {

	std::cout << "Rendering..." << std::endl;

	float delta = 2 / float(CAMERA_VIEW);

	for (int r = 0; r < CAMERA_VIEW; r++) {

		//Percentage of how much the render function has completed
		double helper1 = r;
		double helper2 = CAMERA_VIEW;
		int percent = (helper1 / helper2) * 100;
		std::cout << percent << "%" << std::endl;

		for (int c = 0; c < CAMERA_VIEW; c++) {
			float fov = M_PI / 1;

			//float Py = tan(fov/2) * (2 * (r + 0.5) / CAMERA_VIEW - 1);
			//float Pz = tan(fov/2) * (1 - 2 * (c + 0.5) / CAMERA_VIEW);

			Vertex xp = Vertex(0.0f, r*delta - 0.99875f, c*delta - 0.99875f, 0.0f); //Use wAxis and hAxis
			Vertex ps;

			// choose eye
			if (whichEye == 1)
				ps = eye1;
			if (whichEye == 2)
				ps = eye2;

			//end point
			glm::vec4 D = glm::normalize(xp - ps) *100.0f;	
			Vertex pe = D + ps;
			//Vertex pe = glm::vec4(1.0f, Py, Pz, 1.0f) * 100.0f;
			// equation ray from eye to pixel(i,j), color: white
			Ray ray = Ray(ps, pe, ColorDbl(1, 1, 1));

			//Ray *ray = pixeltoray2(r, c);
			//rayIntersection
			//check if terminated
			ColorDbl color = castRay(ray, 1, scene);

			//Print out color
			//std::cout << "Color: (" << color.x << " , " << color.y << " , " << color.z << ")" << std::endl;

			pixels[c + r*CAMERA_VIEW].setColor(color);

			//pixels[c + r*CAMERA_VIEW].addRay(ray);
		}
	}

	createImage();
}

//JULLES KOD
Ray* Camera::pixeltoray2(int w, int h) {

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.0, pixelStep);


	std::mt19937 gen1(rd());
	auto samplePos = static_cast<float>(dis(rd));
	glm::vec4 pixelPos = pixelplane[0] + (planeWidthAxis * ((w + 1) * pixelStep - samplePos));
	pixelPos += planeHeigthAxis * ((h + 1) * pixelStep - samplePos);

	Ray* r = new Ray(eye1, Vertex(pixelPos.x, pixelPos.y, pixelPos.z, pixelPos.w), ColorDbl(1, 1, 1));
	return r;

}

ColorDbl Camera::castRay(Ray r, int num_reflections, Scene& scene) {

	
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
			//getColor? just nu blir det (0,0,0) (svart) det ska inte bli vitt?
			return intersectedSurface.getSurfaceColor();
		}


		//Bounce - check type - hemisphere or reflect do it in ray/surface
		//MAY NEED TO CHANGE INPUT

		Ray reflectedRay = intersectedSurface.reflectType(r, r.getEnd(), normal);

		//Emitted color
		double theta = glm::angle(reflectedRay.getDirection(), normal);
		ColorDbl emittedColor = intersectedSurface.getSurfaceColor();
		emittedColor = ColorDbl(emittedColor.x*cos(theta), emittedColor.y*cos(theta), emittedColor.z*cos(theta));
		std::cout << emittedColor.x << " " << emittedColor.y << " " << emittedColor.z << std::endl;

		//shadowrays
		ColorDbl illumination = scene.sendShadowRays(r.getEnd(), intersectedSurface.getSurfaceColor(), normal);
		pixelColor += emittedColor;
		pixelColor += illumination; // remake illumiation
		//std::cout << "illumination: (" << illumination.x << " , " << illumination.y << " , " << illumination.z << ")" << std::endl;

		//add Russian roulette?
		if (num_reflections < MAX_REFLECTIONS) {
			int nextReflection = (intersectedSurface.type == "specular") ? num_reflections : (num_reflections + 1);
			//sends out the reflected ray, multiplied with the reflectioncoefficant 

			pixelColor += castRay(reflectedRay, nextReflection, scene) * intersectedSurface.getReflection();
		}


	}
	else if(r.getSphere()){ //intersects with sphere
		normal = r.getSphere()->getNormal(r.getEnd());
		intersectedSurface = r.getSphere()->getSurface();

		//Bounce - check type - hemisphere or reflect do it in ray/surface
		//MAY NEED TO CHANGE INPUT

		Ray reflectedRay = intersectedSurface.reflectType(r, r.getEnd(), normal);

		
		double theta = glm::angle(reflectedRay.getDirection(), normal);
		ColorDbl emittedColor = intersectedSurface.getSurfaceColor();
		emittedColor = ColorDbl(emittedColor.x*cos(theta), emittedColor.y*cos(theta), emittedColor.z*cos(theta));


		//shadowrays
		ColorDbl illumination = scene.sendShadowRays(r.getEnd(), intersectedSurface.getSurfaceColor(), normal);
		pixelColor += emittedColor;
		pixelColor += illumination;

		if (num_reflections < MAX_REFLECTIONS) {
			int nextReflection = (intersectedSurface.type == "specular") ? num_reflections : num_reflections + 1;
			//sends out the reflected ray, multiplied with the reflectioncoefficant 
			pixelColor += castRay(reflectedRay, nextReflection, scene) * intersectedSurface.getReflection();
		}
	}
	else { //No intersection
		//std::cout << "Castray: did not hit a sphere or triangle!" << std::endl;
		return pixelColor;
	}

	//find max rgb value
	maxColor = glm::max(maxColor, glm::max(pixelColor.x, glm::max(pixelColor.y, pixelColor.z)));
	
	// OBS! RETURNS THW WRONG COLOR!!
	
	return pixelColor;
}


void Camera::createImage() {
	
	//FILE *file = fopen("RayTraceOutput.ppm", "wb"); // not secure
	std::string name = "RayTraceOutput.ppm";
	FILE *file;
	errno_t err = fopen_s(&file, name.c_str(), "wb");
	for (int r = 0; r < CAMERA_VIEW; r++) {
		(void)fprintf(file, "P3\n%d %d\n255\n", CAMERA_VIEW, CAMERA_VIEW);
		for (int c = 0; c < CAMERA_VIEW; c++) {
			ColorDbl color = pixels[c + r*CAMERA_VIEW].getColor();
			(void)fprintf(file, "%d %d %d ",
				// /maxColor
				(int)(255 * (color.x / maxColor)),
				(int)(255 * (color.y / maxColor)),
				(int)(255 * (color.z / maxColor))
			);
			std::cout << color.x << " " << color.y << " " << color.z << std::endl;
		}
	}
	fclose(file);
	std::cout << "CreateImage completed" << std::endl;
}

