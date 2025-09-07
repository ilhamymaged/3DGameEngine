#include <Core/Engine.h>

void run_engine(Engine* engine)
{
    Shader* shader = NULL;
    if(!create_shader("basic", &shader)) {
        printf("FAILED TO CREATE A SHADER\n");
    }

    Texture* texture = NULL;
    if(!create_texture(&texture, "wall.jpg")) {
        printf("FAILED TO CREATE A TEXTURE\n");
    }

    Camera camera = {
        .pos = {0.0f, 0.0f, -3.0f},
        .front = {0.0f, 0.0f, -1.0f},
        .up = {0.0f, 1.0f, 0.0f}
    };

    float last_frame = glfwGetTime();
    float deltaTime;

    while(!glfwWindowShouldClose(engine->window->frame)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float current_frame = glfwGetTime();
        deltaTime = current_frame - last_frame;
        last_frame = current_frame;

        //Temp
        if(glfwGetKey(engine->window->frame, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(engine->window->frame, GL_TRUE);

        vec3 temp;
        float speed = deltaTime * 2.5f;
        if(glfwGetKey(engine->window->frame, GLFW_KEY_W) == GLFW_PRESS) {
            glm_vec3_scale(camera.front, speed, temp); 
            glm_vec3_add(camera.pos, temp, camera.pos);
        }

        if(glfwGetKey(engine->window->frame, GLFW_KEY_S) == GLFW_PRESS) {
            glm_vec3_scale(camera.front, speed, temp); 
            glm_vec3_sub(camera.pos, temp, camera.pos);
        }

        mat4 model, view, proj;
        glm_mat4_identity(model);
        glm_mat4_identity(view);
        glm_mat4_identity(proj);

        //View Mat
        vec3 look_pos;
        glm_vec3_add(camera.pos, camera.front, look_pos);
        glm_lookat(camera.pos, look_pos, camera.up, view);

        //Projection Mat
        glm_perspective(glm_rad(45.0f), (float)engine->window->width/engine->window->height, 0.1f, 100.0f, proj);

        use_shader(shader);
        shader_set_mat4(model, "model", shader);
        shader_set_mat4(view, "view", shader);
        shader_set_mat4(proj, "proj", shader);

        use_texture(texture);

        glfwSwapBuffers(engine->window->frame);
        glfwPollEvents();
    }

    destroy_shader(shader);
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
