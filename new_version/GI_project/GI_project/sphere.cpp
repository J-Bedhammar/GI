#include "headers/sphere.h"
#include <cmath>

Sphere::Sphere(float r, Vertex c, Surface s)
	:radius(r), center(c), sphereSurface(s) {
	
}

bool Sphere::raySphereIntersection(Ray &r) {

	const float EPSILON = 0.000000000001f;

	//Sphere object following equations in LE6 "The Scene"
	float sphereRadius = radius;
	Vertex sphereCenter = center;
	Vertex o = r.getStart();	//Start point of ray
	Vertex e = r.getEnd();		//Endpoint of ray
	glm::vec3 l = glm::normalize(e - o);

	//a ray with the starting point (o) and the normalized direction (l) is
	//given by x = o +dl. each value (d) corresponds to one point (x) on the ray.
	// Substitute with (a), (b) and (c): ad^2 + bd + c = 0 <=> d = -(b/2) +- sqrt((b/2)^2 - ac)
	// a = l*l = 1, b = 2l*(o-c), c = (o-c)*.(o-c) - r^2;

	glm::vec3 osC = o - sphereCenter;
	float a = 1.0f;
	float b = glm::dot(2.0f*l, osC);
	float c = glm::dot(osC, osC) - (sphereRadius*sphereRadius);

	//Divide eq. into parts and check if valid root
	float b_half = b / 2.0f;
	float b_ac = (b_half*b_half) - (a*c);

	if (b_ac < -EPSILON) // negative = complex
		return false;

	//d = -(b/2) +- sqrt((b(2)^2 - ac)
	float d1 = -b_half + sqrt(b_ac);
	float d2 = -b_half - sqrt(b_ac);

	if (d1 > EPSILON) {
		//we intersect the spher at point x = 0 + dl;
		Vertex intersectionPoint = Vertex(o.x + d1*l.x, o.y + d1*l.y, o.z + d1*l.z, 1.0f);
		
		//Change endpoint of our ray to the  intersection point
		r.sphereHit(this, intersectionPoint);

		return true;
	}

	if (d2 > EPSILON) {
		//we intersect the spher at point x = o + dl
		Vertex intersectionPoint = Vertex(o.x + d2*l.x, o.y + d2*l.y, o.z + d2*l.z, 1.0f);

		//Change endpoint of our ray to the intersection point
		r.sphereHit(this, intersectionPoint);
		
		return true;
	}

	return false; // no intersection
}