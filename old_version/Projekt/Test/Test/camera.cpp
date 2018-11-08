#include "headers/camera.h"


void Camera::render(Scene& scene) {

	float delta = 2 / float(CAMERA_VIEW);

	for (int r = 0; r < CAMERA_VIEW; r++) {
		for (int c = 0; c < CAMERA_VIEW; c++) {
			
			Vertex xp = Vertex(0.0f, r*delta - 0.99875f, c*delta - 0.99875f, 0.0f);

			Vertex ps;

			// choose eye
			if(whichEye == 1)
				ps = eye1;
			if(whichEye == 2)
				ps = eye2;

			//end point
			glm::vec4 D = (xp - ps) * 100.0f;	//normalize?
			Vertex pe = D + ps;

			// equation ray from eye to pixel(i,j), color: white
			Ray* ray = new Ray(ps, pe, ColorDbl(1, 1, 1));

			//rayIntersection
			castRay(*ray, 0, scene);

			pixels[r][c].addRay(ray);
		}
	}

	std::cout << "If ray in pixel:" << std::endl;
	
	createImage();
}

ColorDbl Camera::castRay(Ray& r, int num_reflections, Scene& scene){
	// Find first intersectionpoint on a surface

	scene.intersections(r);
	Surface intersectedSurface{ ColorDbl(0,1,0), diffuse };
	Direction normal;

	// Intersection with triangle?
	if(r.getTriangle()){
		normal = r.getTriangle()->getNormal();
		intersectedSurface = r.getTriangle()->getSurface();
		std::cout << "Triangle intersection!" << std::endl;
	}
	else if (r.getSphere()){
		normal = r.getSphere()->getNormal(r.getEnd());
		intersectedSurface = r.getSphere()->getSurface();
		std::cout << "Sphere intersection!" << std::endl;
	}
	else{	//No intersection, set values to "default"
		r.setColor(ColorDbl(0,0,1)); 
		normal = Direction(1.0f,0.0f,0.0f);
		//std::cout << "No intersection!" << std::endl;
	}


	// LOCAL LIGHTING
	float reflectedLight = double(glm::dot(normal, -glm::normalize(r.getDirection())));

	// Local light contribution if: diffuse surface, lightsource or max_reflections reached
	if(intersectedSurface.type == diffuse){
		r.setColor(intersectedSurface.getSurfaceColor() * reflectedLight);
		return r.getColor();
	}
	else if (intersectedSurface.type == lightSource){
		r.setColor(ColorDbl{10.0, 10.0, 10.0});
		std::cout << "Lightsource!" << std::endl;
		return r.getColor();
	}
	else if (num_reflections >= MAX_REFLECTIONS){
		r.setColor(intersectedSurface.getSurfaceColor() * reflectedLight);
		return r.getColor();
	}
		
}

// Create the image from the pixel data
void Camera::createImage(){
	std::array<std::array<ColorDbl,CAMERA_VIEW>, CAMERA_VIEW> image;
	std::ofstream red, green, blue;

	double maxIntensity = 0.0;

	// Find max intensity
	for(int r = 0; r < CAMERA_VIEW; r++){
		for(int c = 0; c < CAMERA_VIEW; r++){
			
			ColorDbl color = pixels[r][c].getColor();
			maxIntensity = fmax(maxIntensity, fmax(color.x, fmax(color.y,color.z)));
		}
	}

	// Write to three differet files
	red.open("Documents/MATLAB/TNCG15/red.txt");
	green.open("Documents/MATLAB/TNCG15/green.txt");
	blue.open("Documents/MATLAB/TNCG15/blue.txt");

	for(int r = 0; r < CAMERA_VIEW; r++){
		for(int c = 0; c < CAMERA_VIEW; r++){
			
			image[r][c] = pixels[r][c].getColor();

			red << image[r][c][0] << " ";
			green << image[r][c][1] << " ";
			blue << image[r][c][2] << " ";
			
		}
		red << std::endl;
        green << std::endl;
        blue << std::endl;
	}

	red.close();
	green.close();
	blue.close();
}
