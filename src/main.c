#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <raylib.h>
#include "projection.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_SPEED 10
#define SCALE 5
#define HEADING_LENGTH 30 / SCALE
#define PLAYER_RADIUS SCALE / 2
#define CLIP_DEPTH 0.0001

static const Color BACKGROUND_COLOR = {50, 50, 50};


int main(int argc, char const *argv[])
{
    srand(time(NULL));
    
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple 3d world");

    SetTargetFPS(30);

    struct camera cam = {
        .position={0, 0, 0},
        .rotation={0, 0, 0}
    };

    struct vec3 point = {30, 1, 100};

    struct mesh m = {
        .triangleCount = 2
    };
    
    m.triangles = malloc(sizeof(struct triangle) * 2);
    struct vec3 points1[3] = {
        {.x = 10, .y=10, .z=10},
        {.x = 10, .y=20, .z=10},
        {.x = 20, .y=10, .z=10}
    };
    struct vec3 points2[3] = {
        {.x = 20, .y=20, .z=10},
        {.x = 10, .y=20, .z=10},
        {.x = 20, .y=10, .z=10}
    };
    for (int i = 0; i < 3; i++) {
        m.triangles[0].points[i] = points1[i];
        m.triangles[1].points[i] = points2[i];
    }

    addMesh(&m);

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_E)) {
            struct pixel pos = screenCoordinate(transformPoint(&point, &cam), &cam);
            printf("Screen coor of (%f | %f | %f) => (%i | %i)\n", point.x, point.y, point.z, pos.x, pos.y);
        }

        if (IsKeyDown(KEY_W)) {
            cam.position.z += PLAYER_SPEED * cos(cam.rotation.y);
            cam.position.x += PLAYER_SPEED * sin(cam.rotation.y);
        }
        if (IsKeyDown(KEY_S)) {
            cam.position.z -= PLAYER_SPEED * cos(cam.rotation.y);
            cam.position.x -= PLAYER_SPEED * sin(cam.rotation.y);
        }
        if (IsKeyDown(KEY_A)) {
            cam.position.z -= PLAYER_SPEED * sin(cam.rotation.y);
            cam.position.x -= PLAYER_SPEED * cos(cam.rotation.y);
        }
        if (IsKeyDown(KEY_D)) {
            cam.position.z += PLAYER_SPEED * sin(cam.rotation.y);
            cam.position.x += PLAYER_SPEED * cos(cam.rotation.y);
        }
        if (IsKeyDown(KEY_LEFT)) {
            cam.rotation.y -= PI / 30;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            cam.rotation.y += PI / 30;
        }
        while (cam.rotation.y < 0) {
            cam.rotation.y += 2 * PI;
        }
        while (cam.rotation.y > 2 * PI) {
            cam.rotation.y -= 2 * PI;
        }

        ClearBackground(BACKGROUND_COLOR);
        project(&cam);
    }
    freeMeshs();
    return 0;
}
