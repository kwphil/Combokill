#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include "poly.h"
#include "etc.h"

extern GLfloat* matrix_transform;

float vertices[] = {
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f,-1.0f,
         1.0f,-1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
         1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
         1.0f,-1.0f, 1.0f

};

GLuint VAO, VBO;
GLuint shaderProgram;

/* Returns pointer of the shader program */
int build_shaders(const char* vert_path, const char* frag_path) {
        /* Read files */
        char vert_source[SHADER_SOURCE_SIZE];
        char frag_source[SHADER_SOURCE_SIZE];

        FILE* vf = fopen(vert_path, "r");
        FILE* ff = fopen(frag_path, "r");
        
        fgets(vert_source, SHADER_SOURCE_SIZE, vf);
        fgets(frag_source, SHADER_SOURCE_SIZE, ff);

        fclose(vf);
        fclose(ff);

        /* Compile shaders */
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, (const char*)&vert_source, NULL);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &(const char*)frag_source, NULL);
        glCompileShader(fragmentShader);

        /* Check success of shaders */
        GLint success;
        GLchar infoLog[512];

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success) {
                glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
                fprintf(stderr, "Vertex shader compilation failed:\n%s\n", infoLog);
                exit(2);
        }

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if(!success) {
                glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
                fprintf(stderr, "Fragment Shader Compilation Failed:\n%s\n", infoLog);
                exit(3);
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
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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
