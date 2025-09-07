#ifndef SHADER
#define SHADER

#include <glad/glad.h>
#include <Utility/Utility.h>
#include <stdbool.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Shader 
{
    uint32_t id;
    const char* name;
} Shader;

bool create_shader(const char* path, Shader** out_shader);
void use_shader(const Shader* shader);
void destroy_shader(Shader* shader);

void shader_set_mat4(mat4 mat, const char* name, Shader* shader);

#endif
