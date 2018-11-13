#include <iostream>
#include "headers/triangle.h"
#include "headers/scene.h"

int main(){
	std::cout << "RUN PROGRAM: \n" << std::endl;

	Scene scene;
	
	ColorDbl white{ 1.0f, 1.0f, 1.0f };

	Ray testRay = Ray(Vertex(1.0f, 1.0f, 0.0f, 0.0f), Vertex(-20.0f, 1.0f, 0.0f, 0.0f), white);

	scene.intersections(testRay);

	std::cout << "PROGRAM DONE \n" << std::endl;

	return EXIT_SUCCESS;
}