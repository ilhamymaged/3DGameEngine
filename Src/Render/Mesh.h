#ifndef MESH
#define MESH

#include <glad/glad.h>
#include <cglm/cglm.h>
#include <stdint.h>

typedef struct Vertex {
    vec3 pos;
    vec2 texCoords;
    vec3 normal;
}Vertex;

typedef struct Mesh  {
    Vertex* vertices;
    uint32_t* indices;
    uint32_t vertex_count;
    uint32_t index_count;
    uint32_t VAO;
    uint32_t VBO;
    uint32_t EBO;
}Mesh;

bool create_mesh(Mesh* mesh, Vertex* vertices, uint32_t* indices, uint32_t vertex_count, uint32_t index_count);
void draw_mesh(Mesh* mesh);
void destroy_mesh(Mesh* mesh);

#endif
