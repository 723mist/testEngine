#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "window.hpp"
#include "../graphics/objects.hpp"
#include <iostream>
#include <string>
#include <cmath>
//#include <sstream>

void drawRect2(float pos_x, float pos_y, float scale_x, float scale_y, float red, float green, float blue, float rot) {
   glPushMatrix();
    glTranslatef(pos_x, pos_y, 0.0f);
    glColor3f(red, green, blue); //1.0f 0.5f 0.0f orange
    glRotatef(rot, 0, 0, 1);
    glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.0f, scale_y);
        glVertex2f(scale_x, scale_y);
        glVertex2f(scale_x, 0.0f);
    glEnd();

    glPopMatrix();
}

int EngineWindow::Init(const char* title, int width, int height, bool resizeble){

    if (!glfwInit()){
        std::cerr << "Error init window" << std::endl;
    }

    if (resizeble == true){
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    }
    else {
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    }

    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!window){
        std::cerr << "Error create window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    //glfwSwapInterval(1); //VSync

    static unsigned frameCount = 0;
    double lastTime = glfwGetTime();
    int frames = 0;

    //GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    //glfwSetCursor(window, cursor);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); // теперь (0,0) левый нижний угол
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    std::cout << width << "x" << height;

    int angle = 0;

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        frames++;
        double currentTime = glfwGetTime();
        if (currentTime - lastTime >= 0.3) {
            double fps = frames / (currentTime - lastTime);
            std::string titleWithFPS = std::string(title) + " FPS: " + std::to_string((int)fps); // 60 fps != 60.000 std::to_string((int)fps)
            glfwSetWindowTitle(window, titleWithFPS.c_str());
            std::cout << "FPS: " << (int)fps << std::endl; // 60 fps != 60.000 (int)fps
            frames = 0;
            lastTime = currentTime;
        }

        for (auto obj : objects) {
            obj->draw();
        }

        angle += 1;
        drawRect2(width/2, height/2, 100, 100, 1.0f, 0.5f, 0.0f, angle);

        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
