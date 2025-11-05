#pragma once 

#include <glm/glm.hpp>

class Hitbox {
        glm::vec3 origin;
        glm::vec3 offset;

        
}

void check_collision(Hitbox& hitbox1, Hitbox& hitbox2) {
        glm::vec3 hitbox1_calc = hitbox1.origin+hitbox1.offset;
        glm::vec3 hitbox2_calc = hitbox2.origin+hitbox2.offset;

        hitbox1_calc
}
