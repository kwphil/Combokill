#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>

#include "camera.hpp"
#include "etc.h"
#include "object.hpp"

EXTERN_C const GLfloat* create_transform() {
        static glm::mat4 matrix;

        glm::mat4 model = glm::mat4(1.0f);
 
        // Sorry for the clearly unsafe code, but
        // Taking the Object pointer, converting it to a Camera pointer
        Camera* camera = static_cast<Camera*>(object_list.at(0));

        glm::mat4 view = glm::lookAt(
                camera->origin,
                camera->origin + camera->look_at,
                glm::vec3(0.0, 1.0, 0.0)
        );

        glm::mat4 projection = glm::perspective(
                glm::radians(45.0f),
                800.0f / 600.0f,
                0.5f, 100.0f
        );
        
        matrix = projection * view * model;

        return glm::value_ptr(matrix);
}

