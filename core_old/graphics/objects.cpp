#define PI 3.14159265359f
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

void drawRect(float pos_x, float pos_y, float scale_x, float scale_y, float red, float green, float blue) {
    glPushMatrix();
    glTranslatef(pos_x-(scale_x / 2), pos_y-(scale_y / 2), 0.0f);

    glColor3f(red, green, blue); //1.0f 0.5f 0.0f orange

    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, scale_y);
        glVertex2f(scale_x, scale_y);
        glVertex2f(scale_x, 0.0f);
    glEnd();

    glPopMatrix();
}

void drawCircle(float c_pos_x, float c_pos_y, float radius, int num_segments, float red, float green, float blue)
{
    if (num_segments < 3) return;

    glColor3f(red, green, blue); //1.0f 0.5f 0.0f orange

    glBegin(GL_TRIANGLES);
        for (int i = 0; i < num_segments; i++) {
            float theta1 = 2.0f * PI * float(i) / float(num_segments);
            float theta2 = 2.0f * PI * float(i + 1) / float(num_segments);

            glVertex2f(c_pos_x, c_pos_y);
            glVertex2f(c_pos_x + radius * cosf(theta1), c_pos_y + radius * sinf(theta1));
            glVertex2f(c_pos_x + radius * cosf(theta2), c_pos_y + radius * sinf(theta2));

            glColor3f(red, green, blue);
        }
    glEnd();
}