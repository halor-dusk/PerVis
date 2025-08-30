#include <raylib.h>
#include <raymath.h>
#include <cstdio>
#include "rsrc/perlin_texture.hpp"

int main() {
    InitWindow(896, 512, "PerVis");

    PerlingTexture perlinTexture(128, 128);
    Rectangle src = { 0, 0, (float) perlinTexture.texture.width, (float) perlinTexture.texture.height },
    dest = {
        GetScreenWidth()/2.0f - GetScreenHeight()/2.0f,
        0,
        (float) GetScreenHeight(),
        (float) GetScreenHeight()
    };
    int offsetSpeed = 25;
    int scrollSpeed = 400;
    printf("Texture size: width %d, height %d\n", perlinTexture.texture.width, perlinTexture.texture.height);

    while(!WindowShouldClose()) {
        // Drawing
        BeginDrawing();
            DrawTexturePro(perlinTexture.texture, src, dest, { 0, 0 }, 0, WHITE);
            DrawText(
                "Controls\n"
                "A-W-S-D to move\n"
                "Mouse scoll to zoom\n"
                "Red: high points\n"
                "Blue: deep points",
                16, 16, 24, WHITE
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

        printf("Scale: %2.f\n", perlinTexture.scale);

        // Re generate noise
        perlinTexture.generate();
    }
    CloseWindow();
}
