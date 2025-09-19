#include "renderable.hpp"
#include "objects.hpp"

class Circle : public Renderable {
    float c_pos_x, c_pos_y, radius;
    int num_segments;
    float red, green, blue;
public:
    Circle(float c_pos_x, float c_pos_y, float radius, int num_segments, float red, float green, float blue)
        : c_pos_x(c_pos_x), c_pos_y(c_pos_y), radius(radius), num_segments(num_segments), red(red), green(green), blue(blue) {}

    void draw() override {
        drawCircle(c_pos_x, c_pos_y, radius, num_segments, red, green, blue);
    }
};