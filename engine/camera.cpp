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
        // Normalizes the right vector created from look_at
        return glm::normalize(glm::cross(look_at, glm::vec3(0.0, 1.0, 0.0)));
}

void Camera::move(float speed) {
        // Normalizes the forward vector created from look_at
        glm::forward = glm::normalize(glm::vec3(look_at.x, 0.0, look_at.z));
        // Then applies that to the origin
        origin += forward * speed;
}

void Camera::strafe(float speed) {
        origin += normalize_right() * speed;
}

void move_camera(float speed) {
        // Grab the camera object
        Camera* camera = static_cast<Camera*>(object_list.at(0));

        // And apply movement based on all the keys currently pressed
        if(keymap[SDL_SCANCODE_W]) {
                camera->move(speed);
        }

        if(keymap[SDL_SCANCODE_S]) {
                camera->move(-speed);
        }

        if(keymap[SDL_SCANCODE_A]) {
                camera->strafe(-speed);
        }

        if(keymap[SDL_SCANCODE_D]) {
                camera->strafe(speed);
        }
}

// Process the look_at vec3 based on camera movement
void process_mouse(float sensitivity) {
        // Since these are static, they are only applied once
        static float yaw = -90.0f;  // start facing -Z
        static float pitch = 0.0f;


        Camera* camera = static_cast<Camera*>(object_list.at(0));

        // Deadzone to prevent drift
        if (fabs(mouse_x) < MOUSE_REL_DEADZONE) mouse_x = 0.0f;
        if (fabs(mouse_y) < MOUSE_REL_DEADZONE) mouse_y = 0.0f;

        // Reapply yaw and pitch based on the mouse movement
        yaw += mouse_x * sensitivity;
        pitch -= mouse_y * sensitivity;

        // Prevent weird camera movement from turning too much
        if (pitch > 89.0f)
        pitch = 89.0f;
        if (pitch < -89.0f)
        pitch = -89.0f;

        // And apply the center 
        glm::vec3 direction(
                cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
                sin(glm::radians(pitch)),
                sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        );

        camera->look_at = glm::normalize(direction);
}

