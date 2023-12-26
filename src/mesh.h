#pragma once
#ifndef H_MESH
#define H_MESH

#include <stdlib.h>
#include "vector_math.h"

struct triangle {
    struct vec3 points[3];
};

struct mesh {
    struct triangle *triangles;
    size_t triangleCount;
};

#endif // H_MESH
