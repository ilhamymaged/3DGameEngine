#include <Render/Shader.h>

void shader_set_mat4(mat4 mat, const char* name, Shader* shader) 
{
    uint32_t uniform_loc = glGetUniformLocation(shader->id, name);
    if(uniform_loc == -1) {
        printf("THERE'S NOTHING CALLED: %s\n", name);
        return;
    }
    glUniformMatrix4fv(uniform_loc, 1, GL_FALSE, &mat[0][0]);
}

bool create_shader(const char* name, Shader** out_shader)
{

    if(!name || !out_shader) return false;

    Shader* shader = (Shader*)malloc(sizeof(Shader));
    if(!shader) return false;

    shader->name = strdup(name);

    char v_path[256];
    char f_path[256];

    snprintf(v_path, sizeof(v_path), "../Assets/Shaders/%s.vs", name);
    snprintf(f_path, sizeof(f_path), "../Assets/Shaders/%s.fr", name);

    char* v_source = read_file(v_path);
    char* f_source = read_file(f_path);

    if(!v_source || !f_source) {
        printf("FAILED TO READ SHADER FILES\n");
        free(v_source);
        free(f_source);
        free(shader);
        return false;
    }


    uint32_t v_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v_shader, 1, (const char**)&v_source, NULL);

    glCompileShader(v_shader);
    int success = 0;
    glGetShaderiv(v_shader, GL_COMPILE_STATUS, &success);

    if(success == GL_FALSE)
    {
        int max_length = 0;
        glGetShaderiv(v_shader, GL_INFO_LOG_LENGTH, &max_length);

        char info_log[max_length];
        glGetShaderInfoLog(v_shader, max_length, NULL, &info_log[0]);

        printf("COMPILATION::ERROR::VERTEX: %s\n", &info_log[0]);

        free(v_source);
        free(f_source);
        free(shader);
        return false;
    }

    uint32_t f_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f_shader, 1, (const char**)&f_source, NULL);

    glCompileShader(f_shader);
    glGetShaderiv(f_shader, GL_COMPILE_STATUS, &success);

    if(success == GL_FALSE)
    {
        int max_length = 0;
        glGetShaderiv(f_shader, GL_INFO_LOG_LENGTH, &max_length);

        char info_log[max_length];
        glGetShaderInfoLog(f_shader, max_length, NULL, &info_log[0]);

        printf("COMPILATION::ERROR::FRAGMENT: %s\n", &info_log[0]);

        free(v_source);
        free(f_source);
        free(shader);
        glDeleteShader(v_shader);
        glDeleteShader(f_shader);
        return false;
    }

    shader->id = glCreateProgram();
    glAttachShader(shader->id, v_shader); 
    glAttachShader(shader->id, f_shader);

    glLinkProgram(shader->id);
    glGetProgramiv(shader->id, GL_LINK_STATUS, &success);

    if(success == GL_FALSE)
    {
        int max_length = 0;
        glGetProgramiv(shader->id, GL_INFO_LOG_LENGTH, &max_length);

        char info_log[max_length];
        glGetProgramInfoLog(shader->id, max_length, NULL, &info_log[0]);

        printf("COMPILATION::ERROR::LINKING: %s\n", &info_log[0]);

        free(v_source);
        free(f_source);
        free(shader);
        glDeleteShader(v_shader);
        glDeleteShader(f_shader);
        glDeleteProgram(shader->id);
        return false;
    }

    glDetachShader(shader->id, v_shader);
    glDetachShader(shader->id, f_shader);
    glDeleteShader(v_shader);
    glDeleteShader(f_shader);

    free(v_source);
    free(f_source);

    *out_shader = shader;
    return true;
}

void use_shader(const Shader* shader)
{
    if(shader) glUseProgram(shader->id);
}

void destroy_shader(Shader* shader)
{
    if(shader) {
        glDeleteProgram(shader->id);
        free((void*) shader->name);
        free(shader);
    }
}
