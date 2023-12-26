#include <math.h>
#include "vector_math.h"

struct vec3 vec3_add(struct vec3 *v1, struct vec3 *v2) {
    struct vec3 res = {.x = v1->x + v2->x, .y = v1->y + v2->y, .z = v1->z + v2->z};
    return res;
}

struct vec3 vec3_negate(struct vec3 *vec) {
    struct vec3 negated = {
        .x=-vec->x,
        .y=-vec->y,
        .z=-vec->z
    };
    return negated;
}

struct vec3 vec3_sub(struct vec3 *v1, struct vec3 *v2) {
    struct vec3 snd = vec3_negate(v2);
    return vec3_add(v1, &snd);
}

float vec3_dotp(struct vec3 *v1, struct vec3 *v2) {
    return v1->x * v2->x + v2->y * v1->y + v1->z * v2->z;
}

struct vec3 rotatePointX(struct vec3 *point, float angle) {
    struct vec3 rotatedPoint = {
        .x=point->x,
        .y = point->y * sin(angle) + point->z * cos(angle),
        .z = point->y * cos(angle) - point->z * sin(angle),
    };
    return rotatedPoint;
}

struct vec3 rotatePointY(struct vec3 *point, float angle) {
    struct vec3 rotatedPoint = {
        .x = point->x * cos(angle) - point->z * sin(angle),
        .y=point->y,
        .z = point->x * sin(angle) + point->z * cos(angle)
    };
    return rotatedPoint;
}

struct vec3 rotatePointZ(struct vec3 *point, float angle) {
    struct vec3 rotatedPoint = {
        .x = point->x * cos(angle) - point->y * sin(angle),
        .y = point->x * sin(angle) + point->y * cos(angle),
        .z=point->z
    };
    return rotatedPoint;
}
