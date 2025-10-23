#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include "poly.h"
#include "error.h"

extern GLfloat* matrix_transform;

size_t vertex_len = 9;

float _vertices[] = {
        1.0, 1.0, 1.0,
        -1.0, -1.0, -1.0,
        1.0, -1.0, 1.0
};

float* vertices = _vertices;

GLuint VAO, VBO;
GLuint shaderProgram;

char *read_file(const char *path, size_t *out_len) {
    FILE *fp = fopen(path, "rb");

    if (!fp) return NULL;

    if (fseek(fp, 0, SEEK_END) != 0) { 
            fclose(fp); return NULL; 
    }

    long sz = ftell(fp);
    
    if (sz < 0) { 
            fclose(fp); 
            return NULL; 
    }

    rewind(fp);
    char *buf = malloc((size_t)sz + 1);
    
    if (!buf) { 
            fclose(fp); 
            return NULL; 
    }
    
    size_t n = fread(buf, 1, (size_t)sz, fp);
    fclose(fp);
    buf[n] = '\0';
    
    if(out_len) *out_len = n;
    return buf;
}

/* Returns pointer of the shader program */
int build_shaders(const char* vert_path, const char* frag_path) {
        /* Read files */
        size_t v_size;
        size_t f_size;
        char* vert_source = read_file(vert_path, &v_size);
        char* frag_source = read_file(frag_path, &f_size);       

        if(!(vert_source || frag_source)) {
                fprintf(stderr, "Could not find shader: %s\n", !vert_source ? vert_path : frag_path);
                return ERROR_SHADER_NOT_FOUND;
        }

        /* Compile shaders */
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, (const char* const*)&vert_source, NULL);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, (const char* const*)&frag_source, NULL);
        glCompileShader(fragmentShader);

        /* Check success of shaders */
        GLint success;
        GLchar infoLog[512];

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success) {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                fprintf(stderr, "Vertex shader compilation failed:\n%s\n", infoLog);
                exit(ERROR_SHADER_NOT_LOADED);
        }

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success) {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                fprintf(stderr, "Fragment Shader Compilation Failed:\n%s\n", infoLog);
                exit(ERROR_SHADER_NOT_LOADED);
        }

        /* Link shaders */
        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        /* Delete shaders */
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return shaderProgram;
}

void draw_poly_init() {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertex_len*sizeof(float), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
        glEnableVertexAttribArray(0);

        build_shaders("shaders/vert.glsl", "shaders/frag.glsl");

        glEnable(GL_DEPTH_TEST);
}

void draw_poly() {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        GLuint mvpLoc = glGetUniformLocation(shaderProgram, "MVP");
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, matrix_transform);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 12*3);
}
