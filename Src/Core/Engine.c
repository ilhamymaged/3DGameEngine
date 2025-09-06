#include <Core/Engine.h>

void run_engine(Engine* engine)
{
    while(!glfwWindowShouldClose(engine->window->frame)) {
        glClearColor(0.3, 0.5, 0.1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(engine->window->frame);
        glfwPollEvents();
    }
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

