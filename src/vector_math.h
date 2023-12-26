#pragma once
#ifndef H_VECTOR_MATH
#define H_VECTOR_MATH

#include <math.h>

struct pixel {
    int x, y;
};

struct vec3 {
    float x, y, z;
};

struct vec3 vec3_add(struct vec3 *v1, struct vec3 *v2);
struct vec3 vec3_sub(struct vec3 *v1, struct vec3 *v2);

struct vec3 vec3_negate(struct vec3 *vec);

float vec3_dotp(struct vec3 *v1, struct vec3 *v2);

struct vec3 rotatePointX(struct vec3 *point, float angle);
struct vec3 rotatePointY(struct vec3 *point, float angle);
struct vec3 rotatePointZ(struct vec3 *point, float angle);

#endif // H_VECTOR_MATH
