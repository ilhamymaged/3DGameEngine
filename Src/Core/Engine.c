#include "Render/Mesh.h"
#include "Render/Texture.h"
#include <Core/Engine.h>

void run_engine(Engine* engine)
{
    float vertices[] = {
        // Positions         // TexCoords // Normals
        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   0.0f,  0.0f,  1.0f,

        // Back face
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  0.0f, -1.0f,

        // Left face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,

        // Right face
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   1.0f,  0.0f,  0.0f,

        // Top face
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  1.0f,  0.0f,

        // Bottom face
        -0.5f, -0.5f, -0.5f,  1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
    };

#define NUM_FLOATS_PER_VERTEX 8
#define NUM_VERTICES (sizeof(vertices) / sizeof(float) / NUM_FLOATS_PER_VERTEX)

    Vertex vertexArray[NUM_VERTICES];

    for (int i = 0; i < NUM_VERTICES; ++i) {
        int base = i * NUM_FLOATS_PER_VERTEX;

        glm_vec3_copy(&vertices[base],        vertexArray[i].pos);
        glm_vec2_copy(&vertices[base + 3],    vertexArray[i].texCoords);
        glm_vec3_copy(&vertices[base + 5],    vertexArray[i].normal);
    }


    unsigned int indices[] = {
        // Front face
        0, 1, 2,
        2, 3, 0,

        // Back face
        4, 5, 6,
        6, 7, 4,

        // Left face
        8, 9,10,
        10,11, 8,

        // Right face
        12,13,14,
        14,15,12,

        // Top face
        16,17,18,
        18,19,16,

        // Bottom face
        20,21,22,
        22,23,20
    };
    
    Shader* shader = NULL;
    if(!create_shader("basic", &shader)) {
        printf("FAILED TO CREATE A SHADER\n");
    }

    Mesh* mesh_cube = NULL;
    if(!create_mesh(&mesh_cube, vertexArray, indices,  24, 36)) {
        printf("FAILED TO CREATE A MESH\n");
    }
    
    Texture* texture = NULL;
    if(!create_texture(&texture, "wall.jpg")) {
        printf("FAILED TO CREATE A TEXTURE\n");
    }

    while(!glfwWindowShouldClose(engine->window->frame)) {
        glClearColor(0.3, 0.5, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        use_shader(shader);
        use_texture(texture);
        draw_mesh(mesh_cube);

        glfwSwapBuffers(engine->window->frame);
        glfwPollEvents();
    }

    destroy_shader(shader);
    destroy_mesh(mesh_cube);
    destroy_texture(texture);
}

void destroy_engine(Engine* engine)
{
    if(!engine) return;
    destroy_window(engine->window);
    glfwTerminate();
    free(engine);
}

bool create_engine(int width, int height, const char* name, Engine** out_engine)
{
    if(!out_engine || *out_engine != NULL) {
        printf("THIS ENGINE HAS BEEN INITIALIZED BEFORE\n");
        return false;
    }

    Engine* engine = (Engine*)malloc(sizeof(Engine));
    if(!engine) {
        printf("FAILED TO MALLOC FOR THE ENGINE\n");
        return false;
    }

    if(!init_engine()) {
        printf("FAILED TO INIT ENGINE\n");
        free(engine);
        return false;
    }

    if(!create_window(width, height, name, &engine->window)) {
        printf("FAILED TO CREATE AN GLFW WINDOW");
        glfwTerminate();
        free(engine);
        return false;
    }

    *out_engine = engine;
    return true;
}

bool init_engine()
{
    if(!glfwInit()) {
        printf("FAILED TO INIT GLFW\n");
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSwapInterval(0);
    return true;
}

