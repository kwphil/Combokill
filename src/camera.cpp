#include <SDL3/SDL_scancode.h>

#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "camera.hpp"
#include "keys.hpp"
#include "object.hpp"

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

