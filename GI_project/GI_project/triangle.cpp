#include "headers/triangle.h"

Triangle::Triangle() {
	//std::cout << "Created fake triangle" << std::endl;
}


Triangle::Triangle(Vertex &a, Vertex &b, Vertex &c, Surface s) 
	: v0(a), v1(b), v2(c), triangleSurface(s)
{
	//Calculate the normal
	Direction E1 = Direction(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z); //create edge 1 
	Direction E2 = Direction(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z); //create edge 2

	//Crossproduct of the edges gives the normal
	triangleNormal = glm::normalize(glm::cross(E1, E2));
};



bool Triangle::rayTriangleIntersection(Ray &r) {

	const float EPSILON = 0.00000001f;

	//Get start and endpoints of the ray
	Vertex ps = r.getStart();
	Vertex pe = r.getEnd();
	
	//Create the variables for M�ller Trumbore
	glm::vec3 T = ps - v0;			//Vector between Vertex v0 and the ray startpoint
	glm::vec3 E1 = v1 - v0;			//Edge 1
	glm::vec3 E2 = v2 - v0;			//Edge 2
	glm::vec3 D = pe - ps;			//Direction rayvector from start-end
	glm::vec3 P = glm::cross(D, E2);
	glm::vec3 Q = glm::cross(T, E1);

	//Calculate the determinant
	//The determinant will determine if the ray hits/misses the triangle
	float detA = glm::dot(E1, P); //(DxE2)*E1 = D*(E1xE2) (E1xE2 = triangleNormal)

								  //Three possible outcomes
								  //detA < 0 == triangle is facing the other way
	if (detA < EPSILON)
		return false;

	//detA ~ 0 == normal and ray perpendicular-ish, triangle and ray parallell or almost parallell
	if (fabs(detA) < EPSILON)
		return false;

	//else == Ray hits the triangle
	float invDetA = 1.0f / detA;

	//Barycentric coords (u,v), u,v => 0, u+v <= 1
	//A triangle is given by T(u,v) = (1-u-v)*v0 + u*v1 + v*v2;

	//Compute u and v and check if valid
	float u = glm::dot(P, T) * invDetA;
	if (u < 0.0f || u > 1.0f)
		return false;

	float v = glm::dot(Q, D) * invDetA;
	if (v < 0.0f || u + v > 1.0f)
		return false;

	//u and c are valid, the ray intersects the triangle 
	//compute t
	float t = glm::dot(Q, E2) * invDetA;

	//Check if t valid. If behind eye or if this intersection is behind "another" triangle
	if (t < 0.0f || t > 1.0f)
		return false;

	else {
		//We intersect the triangle with our ray x(t) = ps + t(pe-ps)	
		Direction hitDir = Direction(ps.x, ps.y, ps.z) + t*D;		
		Vertex intersectionPoint = Vertex(float(hitDir.x), float(hitDir.y), float(hitDir.z), 1.0f);
		
		//Change endpoint of our ray to the intersection point
		r.triangleHit(this, intersectionPoint);

		//Set ray color to triangle color but also dependent on normal
		r.setColor(triangleSurface.getSurfaceColor());// *double(glm::dot(triangleNormal, glm::normalize(-D)))); //COULD BE DONE OUTSIDE FUNCTION

		//std::cout << "Hit triangle! Color of triangle: (" << triangleSurface.getSurfaceColor().x << ", " << triangleSurface.getSurfaceColor().y << ", " << triangleSurface.getSurfaceColor().z << ")" << std::endl;

		return true;
	}

}


Vertex Triangle::getRandPoint() {
	
	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution1(0.0, 1.0);
	float randNum1 = distribution1(generator);
	std::uniform_real_distribution<float> distribution2(0.0, (0.99 - randNum1));
	float randNum2 = distribution2(generator);

	if (randNum1 + randNum2 >= 1)
		std::cout << "Error! Random lightpoint outside light triangle!" << std::endl;

	//vertex 1 (2.75,0) vertex 2 ( 7.25,2)
	Vertex V0 = v0;
	Vertex V1 = v1;
	Vertex V2 = v2;
	Vertex V;

	V = V0 + (V1 - V0)* randNum1 + (V2 - V0)*randNum2; 

	return V;
}


//Reference for M�ller Trumbore
// See https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
