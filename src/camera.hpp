#pragma once

#include "object.hpp"

class Camera : public Object {
private:
        glm::vec3 normalize_right();

public:
        glm::vec3 look_at;

        Camera(glm::vec3 origin, glm::vec3 look_at);
        Camera(const Camera& other);
        const glm::vec3 get_look_at() const { return look_at; }
        void move(float speed);
        void strafe(float speed);
};

extern void move_camera(float speed = 0.1f);
extern void process_mouse(float sensitivity);
