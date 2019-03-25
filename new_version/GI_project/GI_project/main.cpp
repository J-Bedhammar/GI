#include <iostream>
#include "headers/triangle.h"
#include "headers/scene.h"
#include "headers/camera.h"

int main(){
	std::cout << "RUN PROGRAM: \n" << std::endl;

	int cameraPos = 1;

	Scene scene;
	Camera camera(cameraPos);

	//Create tetrahedron
	Vertex tetraCenter = Vertex(9.0f, -2.0f, -2.0f, 0.0f);
	Surface tetraSur = Surface(ColorDbl(0.0, 1.0, 0.0), "diffuse");
	Tetrahedron tetra = Tetrahedron(tetraCenter, 3.0, tetraSur);

	//Create sphere
	Vertex sphereCenter = Vertex(9.5f, 2.0f, -3.0f, 0.0f);
	Surface sphereSur = Surface(ColorDbl(1.0, 0.0, 0.0), "specular");
	Sphere sphere = Sphere(1.0f, sphereCenter, sphereSur);
	
	//Create lightsource
	Vertex vl0 = Vertex(2.75f, 0.0f, 4.9f, 0.0f);
	Vertex vl1 = Vertex(7.25f, 2.0f, 4.9f, 0.0f);
	Vertex vl2 = Vertex(7.25f, -2.0f, 4.9f, 0.0f);
	Surface lightSur = Surface(ColorDbl(1.0, 1.0, 1.0), "lightsource");
	Triangle lightTriangle = Triangle(vl0, vl1, vl2, lightSur);
	Lightsource light = Lightsource(lightTriangle);

	//Add objects to scene
	scene.addSphere(sphere);
	scene.addTetrahedron(tetra);
	scene.addLightsource(light);
	
	camera.render(scene); 


	// ---------------------------TEST -----------------------------
	/*ColorDbl white{ 1.0f, 1.0f, 1.0f };

	Ray testRay = Ray(Vertex(1.0f, 1.0f, 0.0f, 0.0f), Vertex(-20.0f, 1.0f, 0.0f, 0.0f), white);

	scene.intersections(testRay); */

	std::cout << "PROGRAM DONE \n" << std::endl;

	return EXIT_SUCCESS;
}