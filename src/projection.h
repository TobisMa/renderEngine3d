#pragma once
#ifndef H_PROJECTION
#define H_PROJECTION

#include <stdlib.h>
#include <raylib.h>
#include "mesh.h"
#include "vector_math.h"

#define CLIP_DEPTH 0.0001

static const Color OUTLINE_COLOR = {255, 255, 255, 255};

struct camera {
    struct vec3 position, rotation;
};


int addMesh(struct mesh *m);
void freeMeshs();
void drawLineSegment(struct vec3 p1, struct vec3 p2, struct camera *cam);
void drawTriangle(struct triangle *triangle, struct camera *cam);
void drawMesh(struct mesh *mesh, struct camera *cam);
struct vec3 transformPoint(struct vec3 *point, struct camera *cam);
struct pixel screenCoordinate(struct vec3 point, struct camera *cam);
void project(struct camera *camera);



#endif // H_PROJECTION
