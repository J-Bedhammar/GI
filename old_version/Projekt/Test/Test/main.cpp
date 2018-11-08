#include <iostream>
#include "glm/glm/glm.hpp"
#include "headers/sphere.h"
#include "headers/tetrahedron.h"
#include "headers/camera.h"
#include "headers/triangle.h"

using namespace std;

Scene scene;
Camera camera;

int main(){

	// Add objects to scene

	// Sphere
	cout << "Adding sphere!" << endl;
	
	ColorDbl red{ 1.0f, 0.0f ,0.0f };
	Sphere redSphere(0.5, Vertex(5,0,0,0), Surface(red, specular));
	
	scene.addSphere(redSphere);
	
	
	// Tetrahedron
	cout << "Adding tetrahedron!" << endl;

	ColorDbl green{ 0.0f ,1.0f , 0.0f};
	Tetrahedron greenTetra(Vertex(3,-2,-2,0), 0.5f, Surface(green,diffuse));
	Surface tetraSurface = greenTetra.getSurface();
	ColorDbl emittedColor = tetraSurface.getSurfaceColor();
	
	scene.addTetrahedron(greenTetra);

	cout << "Color of diffuse surface, before: (0,1,0), after: (" << emittedColor.x << "," << emittedColor.y << "," << emittedColor.z << ")" << endl;
	
	// Lightsource
	cout << "Adding lightsource!" << endl;
	
	Surface white{ ColorDbl{1.0f, 1.0f, 1.0f}, diffuse };
	ColorDbl whiteColor { 1.0f, 1.0f, 1.0f};
	Triangle lightTriangle(Vertex(4,0,5,0), Vertex(5,1,5,0), Vertex(5,-1,5,0), white);
	Lightsource light(lightTriangle);
	
	scene.addLightsource(light);
	
	
	
	// Creating camera
	cout << "Render the scene!" << endl;

	//Camera camera;
	
	//camera.render(scene);
	
	// Test if works?

	Triangle testTriangle(Vertex(0,0,0,0), Vertex(1,0,0,0), Vertex(0,1,0,0), white);
	Ray testRay = Ray(Vertex(1.0f,0.0f,0.0f,0.0f), Vertex(10.f,0.0f,0.0f,0.0f), whiteColor);
	
	if(testTriangle.rayIntersection(testRay))
        std::cout << "intersection!" << std::endl;
    else
        std::cout << "missed triangle" << std::endl;

    if(redSphere.rayIntersection(testRay))
        std::cout << "intersection with sphere!" << std::endl;
    else
        std::cout << "missed sphere" << endl;
    if(greenTetra.rayIntersection(testRay))
		std::cout << "intersection with tetra!" << std::endl;
    else
        std::cout << "missed tetra" << std::endl;
	

	std::cout << std::endl;

	return EXIT_SUCCESS;
}