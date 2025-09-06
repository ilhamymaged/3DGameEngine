#include <Render/Texture.h>

bool create_texture(Texture *texture, const char *name)
{
    if(!texture) {
        printf("THIS TEXTURE: %s HAS BEEN CREATED BEFORE\n", name);
        return false;
    }

    glGenTextures(1, &texture->id);

    return true;
}
