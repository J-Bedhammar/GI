#include "headers/scene.h"

void Scene::createRoom() {

	//colors and surface
	std::string surfaceType = "diffuse";

	Surface white{ ColorDbl{ 1,1,1 }, surfaceType };
	Surface red{ ColorDbl{ 1,0,0 }, surfaceType };
	Surface yellow{ ColorDbl{ 1,1,0 }, surfaceType };
	Surface cyan{ ColorDbl{ 0,1,1 }, surfaceType };
	Surface blue{ ColorDbl{ 0,0,1 }, surfaceType };
	Surface magenta{ ColorDbl{ 1,0,1 }, surfaceType };
	Surface green{ ColorDbl{ 0,1,0 }, surfaceType };
	Surface lightSurface{ ColorDbl{ 1,1,1 }, "lightsource" };

	/* Top-view of room, vertex points and sides
			  a
		FA  /   \  AB		Order: a-b-c-d-e-f
		   f	 b				   AB-BC-CD-DE-EF-FA
		EF |     |  BC
	       e	 c
		DE  \   /  CD
			  d
	*/


	//Vertices
	Vertex aTop = Vertex(-3, 0, 5, 0);		//Top
	Vertex bTop = Vertex(0, 6, 5, 0);
	Vertex cTop = Vertex(10, 6, 5, 0);
	Vertex dTop = Vertex(13, 0, 5, 0);
	Vertex eTop = Vertex(10, -6, 5, 0);
	Vertex fTop = Vertex(0, -6, 5, 0);
	Vertex center = Vertex(5, 0, 5, 0);
	Vertex centerL = Vertex(10, -2, 5, 0);
	Vertex centerR = Vertex(10, 2, 5, 0);

	Vertex aBot = Vertex(-3, 0, -5, 0);		//Bot
	Vertex bBot = Vertex(0, 6, -5, 0);
	Vertex cBot = Vertex(10, 6, -5, 0);
	Vertex dBot = Vertex(13, 0, -5, 0);
	Vertex eBot = Vertex(10, -6, -5, 0);
	Vertex fBot = Vertex(0, -6, -5, 0);

	//Triangles

		//Top
		triangles.push_back(Triangle(aTop, bTop, fTop, white));
		triangles.push_back(Triangle(bTop, center, fTop, white));
		triangles.push_back(Triangle(bTop, cTop, center, white));
		triangles.push_back(Triangle(cTop, dTop, eTop, white));
		triangles.push_back(Triangle(fTop, center, eTop, white));
		triangles.push_back(Triangle(eTop, center, centerL, white));
		triangles.push_back(Triangle(center, cTop, centerR, white));
		Triangle lightTriangle = Triangle(centerL, center, centerR, lightSurface);
		Lightsource light = Lightsource(lightTriangle);
		addLightsource(light);

		//Bot
		triangles.push_back(Triangle(aBot, cBot, bBot, white));
		triangles.push_back(Triangle(cBot, eBot, dBot, white));
		triangles.push_back(Triangle(eBot, aBot, fBot, white));
		triangles.push_back(Triangle(aBot, eBot, cBot, white));

		//Walls
		//AB
		triangles.push_back(Triangle(aTop, aBot, bTop, red));
		triangles.push_back(Triangle(aBot, bBot, bTop, red));
		//BC
		triangles.push_back(Triangle(bTop, bBot, cTop, green));
		triangles.push_back(Triangle(bBot, cBot, cTop, green));
		//CD
		triangles.push_back(Triangle(cTop, cBot, dTop, blue));
		triangles.push_back(Triangle(cBot, dBot, dTop, blue));
		//DE
		triangles.push_back(Triangle(eBot, eTop, dTop, cyan));
		triangles.push_back(Triangle(eBot, dTop, dBot, cyan));
		//EF
		triangles.push_back(Triangle(fBot, fTop, eTop, magenta));
		triangles.push_back(Triangle(fBot, eTop, eBot, magenta));
		//FA
		triangles.push_back(Triangle(aBot, aTop, fTop, yellow));
		triangles.push_back(Triangle(aBot, fTop, fBot, yellow));

}

void Scene::intersections(Ray& r) {

	for (int i = 0; i < spheres.size(); i++) {
		spheres[i].raySphereIntersection(r);
	}
	
	for (int j = 0; j < tetrahedrons.size(); j++) {
		tetrahedrons[j].rayTetraIntersection(r);
	}
	
	for (int k = 0; k < triangles.size(); k++)  //for the walls
	{	
		if (triangles[k].rayTriangleIntersection(r)) {
			//already TRIANGLE if true
			break;
		}
	}

	for (int l = 0; l < lightsources.size(); l++) {
		lightsources[l].rayLightIntersection(r);
	}

}

ColorDbl Scene::sendShadowRays(Vertex &surfacePoint, ColorDbl surfaceColor, Direction normal) {

	ColorDbl black = ColorDbl(0.0, 0.0, 0.0);
	ColorDbl lightcontribution = black;

	//nr of shadow rays 
	for (int i = 0; i < nrShadowRays; i++) {
		//get random point on lightsource
		Vertex randPoint = lightsources.front().getLightTriangle().getRandPoint();
		//randPoint.z = 4.5;
		//randPoint.y = 0.0;

		//shoot ray towards light
		Ray toLight = Ray(surfacePoint, randPoint, black);

		intersections(toLight);

		//hits a sphere
		if (toLight.getSphere()) {
			//make the surfacecolor darker alt do not change the color
			//std::cout << "Hit sphere" << std::endl;
			continue;
		}
		else if (toLight.getTriangle()) {
			if (toLight.getTriangle()->getSurface().type != "lightsource") {
				continue;
			}
			else {
				//std::cout << surfacePoint.x << "," << surfacePoint.y << "," << surfacePoint.z << std::endl;
				//std::cout << "(" << surfaceColor.x << "," << surfaceColor.y << "," << surfaceColor.z << ")" << std::endl;

				Direction lightsourceDir = glm::vec3(randPoint.x - surfacePoint.x, randPoint.y - surfacePoint.y, randPoint.z - surfacePoint.z);
				float distancetoLight = glm::distance(surfacePoint, randPoint);
				float dotProduct = glm::dot(normal, lightsourceDir); // *glm::clamp((double)glm::dot(toLight.getTriangle()->getNormal(), -lightsourceDir), 0.0, 1.0);

				if (dotProduct < 0)
					dotProduct = 0;

				//tweak to change illumination in scene
				float intensity = dotProduct / pow(distancetoLight, 2);
				float emittance = 15.0;
				lightcontribution += surfaceColor * intensity * emittance;


			}
		}
		else {
			//std::cout << "Doesnt hit anything: " << randPoint.x << ", " << randPoint.y << ", " << randPoint.z << std::endl;
		}
	}

	return lightcontribution;
}