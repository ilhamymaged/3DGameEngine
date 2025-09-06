#ifndef TEXTURE
#define TEXTURE

#include <glad/glad.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <Render/stb_image.h>

typedef struct Texture {
    uint32_t id;
} Texture;

bool create_texture(Texture** out_texture, const char* name);
void use_texture(Texture* texture);
void destroy_texture(Texture* texture);

#endif
