#include "headers/scene.h"

void Scene::createRoom() {
	//colors
	Surface white{ ColorDbl{ 1,1,1 }, diffuse };
	Surface red{ ColorDbl{ 1,0,0 }, diffuse };
	Surface yellow{ ColorDbl{ 1,1,0 }, diffuse };
	Surface cyan{ ColorDbl{ 0,1,1 }, diffuse };
	Surface blue{ ColorDbl{ 0,0,1 }, diffuse };
	Surface magenta{ ColorDbl{ 1,0,1 }, diffuse };
	Surface green{ ColorDbl{ 0,1,0 }, diffuse };

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

	Vertex aBot = Vertex(-3, 0, -5, 0);		//Bot
	Vertex bBot = Vertex(0, 6, -5, 0);
	Vertex cBot = Vertex(10, 6, -5, 0);
	Vertex dBot = Vertex(13, 0, -5, 0);
	Vertex eBot = Vertex(10, -6, -5, 0);
	Vertex fBot = Vertex(0, -6, -5, 0);

	//Triangles

		//Top
		triangles.push_back(Triangle(aTop, bTop, cTop, white));
		triangles.push_back(Triangle(cTop, dTop, eTop, white));
		triangles.push_back(Triangle(eTop, fTop, aTop, white));
		triangles.push_back(Triangle(aTop, cTop, eTop, white));

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

	for (int i = 0; i < spheres.size(); i++)
		spheres[i].raySphereIntersection(r);
	
	for (int i = 0; i < tetrahedrons.size(); i++)
		tetrahedrons[i].rayTetraIntersection(r);
	
	for (int i = 0; i < triangles.size(); i++)  //for the walls
	{
		if (triangles[i].rayTriangleIntersection(r))
			//already TRIANGLE if true
			break;
	}

}