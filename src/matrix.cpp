#include <cstdio>
#include <glm/ext/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>


const GLfloat* create_transform() {
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::lookAt(
                glm::vec3(0.0f, 0.0f, 5.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glm::mat4 projection = glm::perspective(
                glm::radians(45.0f),
                800.0f / 600.0f,
                0.1f, 100.0f
        );
        
        static glm::mat4 matrix = projection * view * model;

        return glm::value_ptr(matrix);
}

GLfloat* matrix_transform = const_cast<GLfloat*>(create_transform());

