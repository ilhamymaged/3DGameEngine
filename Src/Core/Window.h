#ifndef WINDOW
#define WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Window {
    GLFWwindow* frame;
    int width;
    int height;
    const char* name;
} Window;

bool create_window(int width, int height, const char* name, Window** out_window);
void destroy_window(Window* window);

#endif
