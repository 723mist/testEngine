#pragma once

#include <vector>
#include <glad/glad.h>

namespace simple_mesh_no_glm {

struct Vertex {
    float position[3]; // x, y, z
    float normal[3];   // nx, ny, nz
    float texCoords[2]; // u, v
};

class Mesh {
public:
    // Конструктор
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
        : vertices(vertices), indices(indices) {
        setupMesh();
    }

    // Деструктор
    ~Mesh() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }

    // Функция отрисовки меша
    void draw() const {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

private:
    // Данные меша
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Идентификаторы буферов OpenGL
    unsigned int VAO, VBO, EBO;

    // Функция настройки буферов OpenGL
    void setupMesh() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // Атрибуты вершин
        // Позиция
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // Нормаль
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3)); // Смещение после 3-х float позиции
        // Текстурные координаты
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 6)); // Смещение после 3-х float позиции и 3-х float нормали

        glBindVertexArray(0);
    }
};

} // namespace simple_mesh_no_glm