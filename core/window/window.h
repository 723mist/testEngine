#pragma once
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <cstdio>
#include <cmath>

#define UlightWindow GLFWwindow*

class Window {
private:
    static void updateProjection(UlightWindow window) {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        float aspect = (float)width / (float)height;
        
        glViewport(0, 0, width, height);
        
        // Ручная реализация gluPerspective
        float fov = 45.0f;
        float near = 0.1f;
        float far = 1000.0f;
        
        float f = 1.0f / tan(fov * 0.5f * 3.14159265f / 180.0f);
        float projMatrix[16] = {
            f/aspect, 0, 0, 0,
            0, f, 0, 0,
            0, 0, (far+near)/(near-far), -1,
            0, 0, (2*far*near)/(near-far), 0
        };
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixf(projMatrix);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, -5);
    }

    static void framebufferSizeCallback(UlightWindow window, int width, int height) {
        updateProjection(window);
    }

public:
    static UlightWindow create(int width = 800, int height = 600, const char* title = "Game") {
        if (!glfwInit()) {
            fprintf(stderr, "Failed to initialize GLFW\n");
            return nullptr;
        }

        UlightWindow window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window) {
            glfwTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(window);
        gladLoadGL();

        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
        updateProjection(window);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return window;
    }

    static void SetIcos(UlightWindow window, const char* icon) {
        GLFWimage _icon[1];
        _icon[0].pixels = stbi_load(icon, &_icon[0].width, &_icon[0].height, 0, 4);
        glfwSetWindowIcon(window, 1, _icon);
        stbi_image_free(_icon[0].pixels);
    }

    static void startFrame(UlightWindow window) {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    static void endFrame(UlightWindow window) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    static bool shouldClose(UlightWindow window) {
        return glfwWindowShouldClose(window);
    }

    static void close(UlightWindow window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};
