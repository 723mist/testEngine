#pragma once
#include <GL/gl.h>
#include <cmath>
#include "../input/keys.h"
#include "../input/mouse.h"
#include "../window/window.h"

#define PI 3.1415926535

float radians(float degrees) {
    return degrees * (PI / 180);
}

class Grid {
private:
    float x = 0; float y = 0; float z = 0;
    float xr = 0; float yr = 0; float zr = 0;

public:

    bool mode = 0;
    float speed = 5;

    Grid() {
        glBegin(GL_LINES);
        glEnd();
    }

    void Camera(UlightWindow window) {
        if (mode == 0) {
            if (pressed(window, keys::W)) {
                x -= speed * cos(radians(yr + 90));
                z -= speed * cos(radians(yr + 90));
            }
            if (pressed(window, keys::S)) {
                x += speed * cos(radians(yr + 90));
                z += speed * cos(radians(yr + 90));
            }
            if (pressed(window, keys::A)) {
                x -= speed * cos(radians(yr));
                z -= speed * cos(radians(yr));
            }
            if (pressed(window, keys::W)) {
                x += speed * cos(radians(yr));
                z += speed * cos(radians(yr));
            }
            glTranslatef(x, y, z);
            glRotatef(xr, 1, 0, 0);
            glRotatef(yr, 0, 1, 0);
            glRotatef(zr, 0, 0, 1);
        }
    }
};
