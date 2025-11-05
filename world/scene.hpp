#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "entity.hpp"

class Scene {
private:
         std::vector<Entity*> entities;
         int floor_size;
         int x_offset;
         int z_offset;

public:
        Scene(int size, int x, int z);
        size_t spawn_entity(const char* file_name, glm::vec3 pos);
        void update();
};
