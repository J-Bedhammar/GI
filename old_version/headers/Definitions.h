#ifndef DEFINITIONS_H
#define DEFINITIONS_H


#include "../glm/glm/glm.hpp"

using Vertex = glm::vec4;
using ColorDbl = glm::vec3;
using Direction = glm::vec3;

enum surfaceType {
	diffuse, specular, lightSource

};

#endif