#include <SDL3/SDL_scancode.h>

#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/trigonometric.hpp>

#include "camera.hpp"
#include "keys.hpp"
#include "object.hpp"

#define MOUSE_REL_DEADZONE 0.001f

Camera::Camera(glm::vec3 origin, glm::vec3 look_at)
: Object(origin), look_at(look_at) { }

Camera::Camera(const Camera& other) 
: Object(other) {
        look_at = other.get_look_at();
}

glm::vec3 Camera::normalize_right() {
        return glm::normalize(glm::cross(look_at, glm::vec3(0.0, 1.0, 0.0)));
}

void Camera::strafe(float speed) {
        origin += normalize_right() * speed;
}

void move_camera(float speed) {
        Camera* camera = static_cast<Camera*>(object_list.at(0));

        if(keymap[SDL_SCANCODE_W]) {
                camera->origin -= glm::vec3(0.0, 0.0, speed);
        }

        if(keymap[SDL_SCANCODE_S]) {
                camera->origin += glm::vec3(0.0, 0.0, speed);
        }

        if(keymap[SDL_SCANCODE_A]) {
                camera->strafe(-speed);
        }

        if(keymap[SDL_SCANCODE_D]) {
                camera->strafe(speed);
        }
}

void process_mouse(float sensitivity) {
    static float yaw = -90.0f;  // start facing -Z
    static float pitch = 0.0f;

    Camera* camera = static_cast<Camera*>(object_list.at(0));

    yaw += mouse_x * sensitivity;
    pitch -= mouse_y * sensitivity;

    // Deadzone to prevent drift
    if (fabs(mouse_x) < MOUSE_REL_DEADZONE) mouse_x = 0.0f;
    if (fabs(mouse_y) < MOUSE_REL_DEADZONE) mouse_y = 0.0f;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    camera->look_at = glm::normalize(direction);
}

