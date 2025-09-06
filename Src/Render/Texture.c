#include <Render/Texture.h>

bool create_texture(Texture **out_texture, const char *name)
{
    if(!out_texture || *out_texture != NULL) {
        printf("THIS TEXTURE: %s HAS BEEN CREATED BEFORE\n", name);
        return false;
    }

    Texture* texture = malloc(sizeof(Texture));
    if (!texture) {
        printf("FAILED TO MALLOC FOR A TEXTURE\n");
        return false;
    }

    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    char path[256];
    snprintf(path, sizeof(path), "../Assets/Textures/%s", name);
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("FAILED TO LOAD THIS IMAGE: %s\n", path);
        free(texture);
        return false;
    }
    stbi_image_free(data);
    *out_texture = texture;
    return true;
}

void use_texture(Texture* texture) 
{
    glBindTexture(GL_TEXTURE_2D, texture->id);
}

void destroy_texture(Texture* texture)
{
    glDeleteTextures(1, &texture->id);
}
