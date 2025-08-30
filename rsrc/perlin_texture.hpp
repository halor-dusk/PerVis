#ifndef PERLIN_TEXTURE_HPP
#define PERLIN_TEXTURE_HPP
#include <raylib.h>

class PerlingTexture {
public:
    Texture2D texture;
    float scale;
    Vector2 offset;

    // Constructors and destructors
    PerlingTexture(int width = 128, int height = 128, float scale = 20.0f);
    ~PerlingTexture();

    void generate();
    Color getColor(float x, float y) const;
private:

};

#endif
