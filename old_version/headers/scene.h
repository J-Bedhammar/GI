#ifndef SCENE_H
#define SCENE_H

#include "triangle.h"
#include "Definitions.h"
#include "sphere.h"
#include "lightsource.h"
#include "tetrahedron.h"
#include <iostream>
#include <vector>

class Scene {
private:
	std::vector<Sphere> spheres;
	std::vector<Tetrahedron> tetrahedrons;
	std::vector<Lightsource> lightsources;

public:
	void createRoom();
	void intersections(Ray& r);

	void addSphere(const Sphere &s) {
		spheres.push_back(s);
		std::cout << "Sphere added" << std::endl;
	}

	void addTetrahedron(const Tetrahedron &t) {
		tetrahedrons.push_back(t);
		std::cout << "Tetrahedron added" << std::endl;
	}

	void addLightsource(const Lightsource &l) {
		lightsources.push_back(l);
		std::cout << "Lightsource added" << std::endl;
	}

};



#endif