#include <stdio.h>
#include <raylib.h>
#include "projection.h"
#include "mesh.h"
#include "vector_math.h"

struct meshList {
    struct mesh *meshs;
    size_t mesh_count;
};

static struct meshList meshs = {
    .meshs = NULL,
    .mesh_count = 0,
};

int addMesh(struct mesh *m) {
    if (meshs.meshs == NULL) {
        meshs.meshs = malloc(sizeof(struct mesh));
        if (meshs.meshs == 0) {
            return 1;
        }
    }
    else {
        struct mesh *tmp = realloc(meshs.meshs, sizeof(struct mesh) * (meshs.mesh_count + 1));
        if (tmp == NULL) {
            return 1;
        }
        meshs.meshs = tmp;
        tmp = NULL;
    }

    meshs.meshs[meshs.mesh_count++] = *m;
    return 0;
}

void freeMeshs() {
    free(meshs.meshs);
    meshs.meshs = NULL;
    meshs.mesh_count = 0;
}

struct vec3 transformPoint(struct vec3 *point, struct camera *cam) {
    struct vec3 transformed = *point;
    transformed = vec3_sub(&transformed, &(cam->position));
    transformed = rotatePointY(&transformed, -cam->rotation.y);
    return transformed;
}

struct pixel screenCoordinate(struct vec3 transformedPoint, struct camera *cam) {
    float depth = transformedPoint.z;
    if (depth == 0) {
        printf("Skipped transforming point. Z=%f\n", transformedPoint.z);
        struct pixel p = {.x = GetScreenWidth() / 2, .y = GetScreenHeight() / 2};
        return p;
    }
    float depthScale = 1 / depth * GetScreenHeight();
    
    struct pixel pixel = {.x=transformedPoint.x, .y=transformedPoint.y};
    pixel.x *= depthScale;
    pixel.y *= depthScale;

    pixel.x += GetScreenWidth() / 2;
    pixel.y += 0;
    
    return pixel;
}

void drawLineSegment(struct vec3 p1, struct vec3 p2, struct camera *cam) {
    struct pixel pixel1, pixel2;
    if (p1.z >= CLIP_DEPTH && p2.z >= CLIP_DEPTH) {
        pixel1 = screenCoordinate(p1, cam);
        pixel2 = screenCoordinate(p2, cam);
    }
    else if (p1.z < CLIP_DEPTH && p2.z < CLIP_DEPTH) {
        return;
    }
    else {
        struct vec3 front, back;
        if (p1.z >= CLIP_DEPTH) {
            front = p1;
            back = p2;
        }
        else {
            front = p2;
            back = p1;
        }

        float size = front.z - back.z;
        float percentage = front.z / size;
        float clipPos = front.x + (back.x - front.x) * percentage;
        back.x = clipPos;
        back.y = back.y;
        back.z = CLIP_DEPTH;

        pixel1 = screenCoordinate(front, cam);
        pixel2 = screenCoordinate(back, cam);

    } 
    DrawLine(pixel1.x, pixel1.y, pixel2.x, pixel2.y, OUTLINE_COLOR);
}

void drawTriangle(struct triangle *triangle, struct camera *cam) {
    struct vec3 p1 = transformPoint(&triangle->points[0], cam);
    struct vec3 p2 = transformPoint(&triangle->points[1], cam);
    struct vec3 p3 = transformPoint(&triangle->points[2], cam);

    drawLineSegment(p1, p2, cam);
    drawLineSegment(p2, p3, cam);
    drawLineSegment(p3, p1, cam);
}

void drawMesh(struct mesh *mesh, struct camera *cam) {
    for (int i = 0; i < mesh->triangleCount; i++) {
        struct triangle tri = mesh->triangles[i];
        drawTriangle(&tri, cam);
    }
}

void project(struct camera *cam) {
    BeginDrawing();
    for (int i = 0; i < meshs.mesh_count; i++) {
        struct mesh mesh = meshs.meshs[i];
        drawMesh(&mesh, cam);
    }
    EndDrawing();
}
