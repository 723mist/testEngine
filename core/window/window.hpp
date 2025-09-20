#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "graphics/renderable.hpp"
#include <iostream>
#include <vector>

class EngineWindow{
    std::vector<Renderable*> objects;
public:
    void add(Renderable* obj) {
        objects.push_back(obj);
    }

    int width, height;

    int Init(const char* title = "VEngine window 500x500", int width = 500, int height = 500, bool resizeble = true);
};
