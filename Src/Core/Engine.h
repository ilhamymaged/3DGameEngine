#ifndef ENGINE
#define ENGINE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Core/Window.h>
#include <Render/Shader.h>
#include <Render/Mesh.h>
#include <Render/Texture.h>

typedef struct Engine {
    Window* window;
} Engine;

bool init_engine();
bool create_engine(int width, int height, const char* name, Engine** out_engine);
void run_engine(Engine* engine);
void destroy_engine(Engine* engine);

#endif
