#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <array>
#include "../vector.h"

#define SetMouse glfwSetCursorPosCallback

Vec2 GetPosMouse(GLFWwindow* window) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return {static_cast<float>(xpos), static_cast<float>(ypos)};
}
