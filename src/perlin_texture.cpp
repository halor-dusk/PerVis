#include "../rsrc/perlin_texture.hpp"
#include "../stb_perlin.h"
#include <cmath>
#include <raylib.h>

PerlingTexture::PerlingTexture(int width, int height, float scale)
: scale(scale) {
    // Create am empty texture
    Image perlinImage = GenImageColor(width, height, WHITE);
    this->texture = LoadTextureFromImage(perlinImage);
    UnloadImage(perlinImage);

    // Generate first perling noise
    this->generate();
}

PerlingTexture::~PerlingTexture() {

}

void PerlingTexture::generate() {
    Image perlinImage = GenImageColor(this->texture.width, this->texture.height, WHITE);

    for (int x = 0; x < perlinImage.width; x++) {
        for (int y = 0; y < perlinImage.height; y++) {
            Color color = getColor(x, y);
            ImageDrawPixel(&perlinImage, x, y, color);
        }
    }

    UnloadTexture(this->texture);
    this->texture = LoadTextureFromImage(perlinImage);
    UnloadImage(perlinImage);
}

Color PerlingTexture::getColor(float x, float y) const {
    // Get normalized coords
    float nx = (float) x/this->texture.width,
    ny = (float) y/this->texture.height;

    // Generate noise
    float noise = stb_perlin_noise3(nx*this->scale + offset.x, ny*this->scale + offset.y, 0.0f, 0, 0, 0);
    noise = noise/2.0f + 0.5f;

    // Convert from -1 to 1, to 0, 1 and covert to color so we can visualize
    unsigned char sample = static_cast<unsigned char>(noise*255);

    Color colors[3] = {
        { 0x00, 0x00, sample, 0xFF }, // 0.0
        { 0x00, sample, 0x00, 0xFF }, // 0.5
        { sample, sample, sample, 0xFF } // 1.0
    };

    return colors[(int) std::floor(noise*3.0f)];
}
