#include <GL/glew.h>
#include <GLFW/glfw3.h>

void drawRect(float pos_x, float pos_y, float scale_x, float scale_y, float red, float green, float blue) {
    glPushMatrix();
    glTranslatef(pos_x, pos_y, 0.0f);

    glColor3f(red, green, blue); //1.0f 0.5f 0.0f

    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, scale_y);
        glVertex2f(scale_x, scale_y);
        glVertex2f(scale_y, 0.0f);
    glEnd();

    glPopMatrix();
}