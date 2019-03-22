#ifndef SCENE_H
#define SCENE_H

#include "triangle.h"
#include "definitions.h"
#include "sphere.h"
#include "lightsource.h"
#include "tetrahedron.h"
#include <vector>

class Scene {
private:
	std::vector<Sphere> spheres;
	std::vector<Triangle> triangles;
	std::vector<Tetrahedron> tetrahedrons;
	std::vector<Lightsource> lightsources;

	const int nrShadowRays = 2;

public:
	Scene() {
		std::cout << "Created room" << std::endl;
		createRoom();
	}
	~Scene() = default;
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

	ColorDbl sendShadowRays(Vertex &surfacePoint, ColorDbl surfaceColor, Direction normal);

};



#endif