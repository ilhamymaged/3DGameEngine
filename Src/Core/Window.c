#include <Core/Window.h>

bool create_window(int width, int height, const char* name, Window **out_window) 
{
    if(!out_window || *out_window != NULL) {
        printf("THIS WINDOW HAS BEEN INITIALIZED BEFORE\n");
        return false;
    }

    Window* window = (Window*)malloc(sizeof(Window));
    if(!window) {
        printf("FAILED TO MALLOC FOR THE WINDOW\n");
        return false;
    }

    window->frame = glfwCreateWindow(width, height, name, NULL, NULL);
    if(!window->frame) {
        printf("FAILED TO CRETE A WINDOW\n");
        free(window);
        glfwTerminate();
        return false;
    }
    printf("WINDOW HAS BEEN CREATED\n");

    glfwMakeContextCurrent(window->frame);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        printf("FAILED TO INIT GLAD\n");
        glfwDestroyWindow(window->frame);
        free(window);
        return false;
    }
    printf("GL Version: %s\n", glGetString(GL_VERSION));

    *out_window = window;
    return true;
}

void destroy_window(Window* window) 
{
    glfwDestroyWindow(window->frame);
}
