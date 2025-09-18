#pragma once
#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include "mesh.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <array>
#include <fstream>

void Rect(float pos[2], float size[2], float rotate, float color[3]) {

    glPushMatrix();

    glTranslatef(pos[0], pos[1], 0.0);
    glRotatef(rotate, 0.0f, 0.0f, 1.0f);
    glScalef(size[0], size[1], 1.0);

    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(0, 1);
        glVertex2f(1, 1);
        glVertex2f(1, 0);
    glEnd();

    glPopMatrix();
}

class Sprite {
private:
    GLuint textureID;

public:
    bool load(const char* file) {
        GLFWimage image;
        image.pixels = stbi_load(file, &image.width, &image.height, NULL, 4);
        if (!image.pixels) {
            printf("Error loading image: %s\n", file);
            return false;
        }

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 
                    0, GL_RGBA, GL_UNSIGNED_BYTE, image.pixels);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        stbi_image_free(image.pixels);
        
        return true;
    }

    void Draw(std::array<float, 3> pos = {0, 0, 0}, 
              std::array<float, 3> scale = {1, 1, 1}, 
              std::array<float, 3> rotate = {0, 0, 0}) {
        glDisable(GL_CULL_FACE);
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glBindTexture(GL_TEXTURE_2D, textureID);

        glPushMatrix();
        glTranslatef(pos[0], pos[1], pos[2]);
        glRotatef(rotate[0], 1.0f, 0.0f, 0.0f);
        glRotatef(rotate[1], 0.0f, 1.0f, 0.0f);
        glRotatef(rotate[2], 0.0f, 0.0f, 1.0f);
        glScalef(scale[0], -scale[1], scale[2]);

        glBegin(GL_QUADS);
            glTexCoord2f(1.0f, 1.0f); glVertex2f(0.5f, 0.5f);
            glTexCoord2f(0.0f, 1.0f); glVertex2f(-0.5f, 0.5f);
            glTexCoord2f(0.0f, 0.0f); glVertex2f(-0.5f, -0.5f);
            glTexCoord2f(1.0f, 0.0f); glVertex2f(0.5f, -0.5f);
        glEnd();
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
        glEnable(GL_CULL_FACE);
    }

    void cleanup() {
        glDeleteTextures(1, &textureID);
    }
};

class Entity {
    Entity(const char* name, const char* texture) {}
};
