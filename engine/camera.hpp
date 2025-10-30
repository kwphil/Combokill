#pragma once

#include "object.hpp"

/// @brief the camera
class Camera : public Object {
private:
        glm::vec3 normalize_right();

public:
        /// @brief Stores the rotations in the object
        glm::vec3 look_at;

        Camera(glm::vec3 origin, glm::vec3 look_at);
        Camera(const Camera& other);

        /// @brief moves the camera along z axis (from the perspective of the camera)
        /// @param speed How fast the camera is moving forward. Can be negative to move backward
        void move(float speed);
        /// @brief moves the camera along x axis (from the perspective of the camera)
        /// @param speed How fast the camera is moving left. Can be negative to move backward
        void strafe(float speed);
};

/// @brief A wrapper to move the camera based on inputs
/// @param speed An optional parameter to check how fast to move. Do not use negatives
extern void move_camera(float speed = 0.1f);
/// @brief A wrapper to process the mouse to rotate the camera
/// @param speed An optional parameter to check how fast to rotate.
extern void process_mouse(float sensitivity = 0.1f);
