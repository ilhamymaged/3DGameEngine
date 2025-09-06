#include <Core/Engine.h>

#define SCR_WIDTH 1280
#define SCR_HEIGHT 720
#define NAME "3D GAME ENGINE"

int main() 
{
    Engine* engine = NULL;
    if(!create_engine(SCR_WIDTH, SCR_HEIGHT, NAME, &engine)) {
        printf("FAILED TO CREATE THE ENGINE\n");
        return -1;
    }
    run_engine(engine);
    destroy_engine(engine);
    return 0;
}
