#include "headers/scene.h"

void Scene::createRoom() {
	//colors
	Surface white{ ColorDbl{1,1,1 }, diffuse };
	Surface red{ ColorDbl{ 1,0,0 }, diffuse};
	Surface yellow{ ColorDbl{ 1,1,0 }, diffuse};
	Surface cyan{ ColorDbl{ 0,1,1 }, diffuse};
	Surface blue{ ColorDbl{ 0,0,1 }, diffuse};
	Surface magenta{ ColorDbl{ 1,0,1 }, diffuse};
	Surface green{ ColorDbl{ 0,1,0 }, diffuse};

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
	const int num_Triangles = 20;
	Triangle triangles[num_Triangles] = {

	//Top
		Triangle(aTop,bTop,cTop,white),
		Triangle(cTop,dTop,eTop,white),
		Triangle(eTop,fTop,aTop,white),
		Triangle(aTop,cTop,eTop,white),

	//Bot
		Triangle(aBot,cBot,bBot,white),
		Triangle(cBot,eBot,dBot,white),
		Triangle(eBot,aBot,fBot,white),
		Triangle(aBot,eBot,cBot,white),
	
	//Walls
		//AB
		Triangle(aTop,aBot,bTop,red),
		Triangle(aBot,bBot,bTop,red),
		//BC
		Triangle(bTop,bBot,cTop,green),
		Triangle(bBot,cBot,cTop,green),
		//CD
		Triangle(cTop,cBot,dTop,blue),
		Triangle(cBot,dBot,dTop,blue),
		//DE
		Triangle(eBot,eTop,dTop,cyan),
		Triangle(eBot,dTop,dBot,cyan),
		//EF
		Triangle(fBot,fTop,eTop,magenta),
		Triangle(fBot,eTop,eBot,magenta),
		//FA
		Triangle(aBot,aTop,fTop,yellow),
		Triangle(aBot,fTop,fBot,yellow)
	};
	
}

void Scene::intersections(Ray& r) {

	for (int i = 0; i < spheres.size(); i++)
		spheres[i].rayIntersection(r);

	for (int i = 0; i < tetrahedrons.size(); i++)
		tetrahedrons[i].rayIntersection(r);

	for (int i = 0; i< T_SIZE; i++)  //for the walls
	{
		if (triangles[i].rayIntersection(r))
			//already TRIANGLE if true
			break; 
	}

}