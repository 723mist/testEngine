#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void drawRect(float pos_x = 0, float pos_y = 0, float scale_x = 100, float scale_y = 100, float red = 1.0f, float green = 1.0f, float blue = 1.0f);
void drawCircle(float c_pos_x = 0, float c_pos_y = 0, float radius = 10, int num_segments = 10, float red = 1.0f, float green = 1.0f, float blue = 1.0f);
