#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../hpp/window.hpp"
#include <iostream>
#include <string>
//#include <sstream>

int EngineWindow::Init(const char* title, int width, int height){

    if (!glfwInit()){
        std::cerr << "Error init window" << std::endl;
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

    GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
    glfwSetCursor(window, cursor);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        frames++;
        double currentTime = glfwGetTime();
        if (currentTime - lastTime >= 1.0) {
            std::cout << "FPS: " << frames << std::endl;
            std::string titleWithFPS = std::string(title) + " FPS: " + std::to_string(int(frames));
            glfwSetWindowTitle(window, titleWithFPS.c_str());
            frames = 0;
            lastTime = currentTime;
        }

        glfwPollEvents();

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
