#include <cstdio>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

#include "object.hpp"

GLfloat* matrix_transform;

const GLfloat* create_transform() {
        glm::mat4 model = glm::mat4(1.0f);
        
        printf("%d", object_list.size());
        fflush(stdout);

        glm::mat4 view = glm::lookAt(
                object_list.at(0).get_origin(), 
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
        );

        glm::mat4 projection = glm::perspective(
                glm::radians(45.0f),
                800.0f / 600.0f,
                0.1f, 100.0f
        );
        
        static glm::mat4 matrix = projection * view * model;

        matrix_transform = const_cast<GLfloat*>(glm::value_ptr(matrix));
        return glm::value_ptr(matrix);
}

