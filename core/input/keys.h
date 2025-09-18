#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define pressed glfwGetKey

inline bool unpressed(GLFWwindow* window, int key) {
    if (pressed(window, key) != true) {
        return true;
    }
}

namespace keys {
    constexpr int Q = GLFW_KEY_Q;
    constexpr int W = GLFW_KEY_W;
    constexpr int E = GLFW_KEY_E;
    constexpr int R = GLFW_KEY_R;
    constexpr int T = GLFW_KEY_T;
    constexpr int Y = GLFW_KEY_Y;
    constexpr int U = GLFW_KEY_U;
    constexpr int I = GLFW_KEY_I;
    constexpr int O = GLFW_KEY_O;
    constexpr int P = GLFW_KEY_P;
    constexpr int A = GLFW_KEY_A;
    constexpr int S = GLFW_KEY_S;
    constexpr int D = GLFW_KEY_D;
    constexpr int F = GLFW_KEY_F;
    constexpr int G = GLFW_KEY_G;
    constexpr int H = GLFW_KEY_H;
    constexpr int J = GLFW_KEY_J;
    constexpr int K = GLFW_KEY_K;
    constexpr int L = GLFW_KEY_L;
    constexpr int Z = GLFW_KEY_Z;
    constexpr int X = GLFW_KEY_X;
    constexpr int C = GLFW_KEY_C;
    constexpr int V = GLFW_KEY_V;
    constexpr int B = GLFW_KEY_B;
    constexpr int N = GLFW_KEY_N;
    constexpr int M = GLFW_KEY_M;
    constexpr int F1  = GLFW_KEY_F1;
    constexpr int F2  = GLFW_KEY_F2;
    constexpr int F3  = GLFW_KEY_F3;
    constexpr int F4  = GLFW_KEY_F4;
    constexpr int F5  = GLFW_KEY_F5;
    constexpr int F6  = GLFW_KEY_F6;
    constexpr int F7  = GLFW_KEY_F7;
    constexpr int F8  = GLFW_KEY_F8;
    constexpr int F9  = GLFW_KEY_F9;
    constexpr int F10 = GLFW_KEY_F10;
    constexpr int F11 = GLFW_KEY_F11;
    constexpr int F12 = GLFW_KEY_F12;
    constexpr int LCTRL  = GLFW_KEY_LEFT_CONTROL;
    constexpr int RCTRL  = GLFW_KEY_RIGHT_CONTROL;
    constexpr int LSHIFT = GLFW_KEY_LEFT_SHIFT;
    constexpr int RSHIFT = GLFW_KEY_RIGHT_SHIFT;
    constexpr int LALT   = GLFW_KEY_LEFT_ALT;
    constexpr int RALT   = GLFW_KEY_RIGHT_ALT;
    constexpr int TAB    = GLFW_KEY_TAB;
    constexpr int SPACE  = GLFW_KEY_SPACE;
    constexpr int ENTER  = GLFW_KEY_ENTER;
    constexpr int ESC    = GLFW_KEY_ESCAPE;
}