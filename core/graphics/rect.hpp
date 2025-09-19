#include "renderable.hpp"
#include "objects.hpp"

class Rect : public Renderable {
    float pos_x, pos_y, size_x, size_y;
    float red, green, blue;
public:
    Rect(float pos_x, float pos_y, float size_x, float size_y,
         float red, float green, float blue)
        : pos_x(pos_x), pos_y(pos_y),
          size_x(size_x), size_y(size_y),
          red(red), green(green), blue(blue) {}

    void draw() override {
        drawRect(pos_x, pos_y, size_x, size_y, red, green, blue);
    }
};