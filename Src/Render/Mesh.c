#include <Render/Mesh.h>

bool create_mesh(Mesh** out_mesh, Vertex* vertices, uint32_t* indices, uint32_t vertex_count, uint32_t index_count)
{
    if (!out_mesh || !vertices || !indices || *out_mesh != NULL) {
        printf("CREATE MESH: NULL ARGUMENT!\n");
        return false;
    }

    Mesh* mesh = malloc(sizeof(Mesh));
    if (!mesh) {
        printf("FAILED TO MALLOC FOR A MESH\n");
        return false;
    }

    // Copy vertex and index data into mesh
    mesh->vertices = malloc(sizeof(Vertex) * vertex_count);
    memcpy(mesh->vertices, vertices, sizeof(Vertex) * vertex_count);

    mesh->indices = malloc(sizeof(uint32_t) * index_count);
    memcpy(mesh->indices, indices, sizeof(uint32_t) * index_count);

    mesh->vertex_count = vertex_count;
    mesh->index_count = index_count;

    glGenBuffers(1, &mesh->VBO);
    glGenBuffers(1, &mesh->EBO);
    glGenVertexArrays(1, &mesh->VAO);

    glBindVertexArray(mesh->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex_count, mesh->vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * index_count, mesh->indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    *out_mesh = mesh;
    return true;
}

void draw_mesh(Mesh* mesh) 
{
    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, 0);
}

void destroy_mesh(Mesh* mesh) 
{
     if (!mesh) return;

    glDeleteBuffers(1, &mesh->VBO);
    glDeleteBuffers(1, &mesh->EBO);
    glDeleteVertexArrays(1, &mesh->VAO);

    free(mesh->vertices);
    free(mesh->indices);
    free(mesh);
}
