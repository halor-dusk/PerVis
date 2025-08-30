#include <raylib.h>
#include <raymath.h>
#include <cstdio>
#include "rsrc/perlin_texture.hpp"

int main() {
    InitWindow(896, 512, "PerVis");

    PerlingTexture perlinTexture(128, 128);
    perlinTexture.offset = {
        (float) GetRandomValue(-9999, 9999),
        (float) GetRandomValue(-9999, 9999)
    };
    Rectangle src = {
        0,
        0,
        (float) perlinTexture.texture.width,
        (float) perlinTexture.texture.height
    },
    dest = {
        GetScreenWidth()/2.0f - GetScreenHeight()/2.0f,
        0,
        (float) GetScreenHeight(),
        (float) GetScreenHeight()
    };
    float offsetSpeed = 20,
    scrollSpeed = 400;
    printf("Texture size: width %d, height %d\n", perlinTexture.texture.width, perlinTexture.texture.height);

    while(!WindowShouldClose()) {
        // Drawing
        BeginDrawing();
            DrawTexturePro(perlinTexture.texture, src, dest, { 0, 0 }, 0, WHITE);
            DrawText(
                "Controls\n"
                "A-W-S-D: move\n"
                "Mouse scoll: zoom\n"
                "R: re-generate noise\n"
                "Red: high points\n"
                "Green: mid points\n"
                "Blue: deep points",
                16, 16, 16, WHITE
            );
        EndDrawing();

        // Update
        float deltaTime = GetFrameTime();

        // Move though texture
        Vector2 velocity = { 0.0f, 0.0f };

        if (IsKeyDown(KEY_A)) {
            velocity.x = -1;
        } else if (IsKeyDown(KEY_D)) {
            velocity.x = 1;
        }

        if (IsKeyDown(KEY_W)) {
            velocity.y = -1;
        } else if (IsKeyDown(KEY_S)) {
            velocity.y = 1;
        }

        velocity = Vector2Normalize(velocity)*offsetSpeed;
        perlinTexture.offset += velocity*deltaTime;

        printf("Position: X %0.f, Y %0.f\n", perlinTexture.offset.x, perlinTexture.offset.y);

        // Change scale
        float mouseWheel = GetMouseWheelMove();
        perlinTexture.scale -= mouseWheel*scrollSpeed*deltaTime;
        perlinTexture.scale = Clamp(perlinTexture.scale, 0, 100);
        offsetSpeed = perlinTexture.scale;

        printf("Scale: %f\n", perlinTexture.scale);

        // Completely re generate noise
        if (IsKeyPressed(KEY_R)) {
            perlinTexture.offset = {
                (float) GetRandomValue(-9999, 9999),
                (float) GetRandomValue(-9999, 9999)
            };

            printf("Noise re generated\n");
        }

        // Re generate noise
        perlinTexture.generate();
    }
    CloseWindow();
}
