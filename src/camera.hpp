#pragma once
//prevents duplication

#include "object.hpp" //includes contents from object.hpp

class Camera : public Object { //creates a class and a object that can be used anywhere
private:
        glm::vec3 normalize_right(); //calculates right vector and gives it a value of 1 for only this file

public:
        glm::vec3 look_at; //coordinants of what the camera's posision is

        Camera(glm::vec3 origin, glm::vec3 look_at); //uses 3 vectors to figure out what the posiston of the camera is and what it is lookig at
        Camera(const Camera& other); //coppies an existing camera constructor
        const glm::vec3 get_look_at() const { return look_at; } //retrieves 3d vector
        void strafe(float speed); //camera's movement speed
};

extern void move_camera(); //lets the compiler know move_camera() is on a different file
