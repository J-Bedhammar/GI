#ifndef DEFINITIONS_H
#define DEFINITIONS_H
#define M_PI 3.14159f

#include "glm.hpp"
#include <iostream>
#include <cmath>

using Vertex = glm::vec4;
using ColorDbl = glm::vec3;
using Direction = glm::vec3;

enum surfaceType {
	diffuse,
	specular,
	lightsource

};

#endif