#ifndef SCENE_H
#define SCENE_H

#include "triangle.h"
#include "definitions.h"
#include "sphere.h"
#include "lightsource.h"
#include "tetrahedron.h"

class Scene() {
private:
	Sphere sphere;
	Tetrahedron tetrahedron;
	Lightsource lightsource;
public:
	void createRoom();
	void intersections(Ray& r);

	void addSphere(const Sphere &s) {
		sphere.push_back(s);
		std::cout << "Sphere added" << std::endl;
	}

	void addTetrahedron(const Tetrahedron &t) {
		tetrahedron.push_back(t);
		std::cout << "Tetrahedron added" << std::endl;
	}

	void addLightsource(const Lightsource &l) {
		lightsource.push_back(l);
		std::cout << "Lightsource added" << std::endl;
	}

}



#endif