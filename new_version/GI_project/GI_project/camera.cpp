#include "headers/camera.h"
//CASTRAY


void Camera::render(Scene& scene) {

	float delta = 2 / float(CAMERA_VIEW);

	for (int r = 0; r < CAMERA_VIEW; r++) {
		for (int c = 0; c < CAMERA_VIEW; c++) {

			Vertex xp = Vertex(0.0f, r*delta - 0.99875f, c*delta - 0.99875f, 0.0f);

			Vertex ps;

			// choose eye
			if (whichEye == 1)
				ps = eye1;
			if (whichEye == 2)
				ps = eye2;

			//end point
			glm::vec4 D = (xp - ps) * 100.0f;	//normalize?
			Vertex pe = D + ps;

			// equation ray from eye to pixel(i,j), color: white
			Ray* ray = new Ray(ps, pe, ColorDbl(1, 1, 1));

			//rayIntersection
			//INSERT CASTRAY


			pixels[r][c].addRay(ray);
		}
	}

	createImage();
}

ColorDbl Camera::castRay(Ray& r, int num_reflections, Scene& scene) {
	
	ColorDbl pixelColor;
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
		if (r.getTriangle()->getSurface().type == lightsource) {
			//getColor? just nu blir det (0,0,0) (svart) det ska inte bli vitt?
			return intersectedSurface.getSurfaceColor();
		}


		//Bounce - check type - hemisphere or reflect do it in ray/surface
		//reflectType()

		//getSurfaceColor  Emitted color




	}
	else if(r.getSphere()){ //intersects with sphere
		normal = r.getSphere()->getNormal(r.getEnd);
		intersectedSurface = r.getSphere()->getSurface();

	}
	else { //No intersection

	}


	//calculate pixel radience
	//surfacemodel? diffuse or specular or lightsource
	//BRDF/reflect
	// color emittance = output

	//shadowrays

	//hitta max rbg?? /egen funktion?
	//sätt pixel till color/max
	
	//check if it should be terminated
	//if not: repeat


}