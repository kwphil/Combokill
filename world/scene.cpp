#include <cstring>
#include <iostream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../core/assets.h"
#include "scene.hpp"

#define FLOOR_DATA_OFFSET_VAL 9*sizeof(float)

const float floor_m1[] = {
        -1.0, 0.0, 1.0,
         1.0, 0.0,-1.0,
         1.0, 0.0, 1.0
};

const float floor_m2[] = {
        -1.0, 0.0, 1.0,
         1.0, 0.0,-1.0,
        -1.0, 0.0, 1.0
};


Scene::Scene(int size, int x, int z)
: entities(), floor_size(size), x_offset(x), z_offset(z) { 
        
}

size_t Scene::spawn_entity(const char* file_name, glm::vec3 pos) {
        size_t data_size;
        float* asset = asset_csv(file_name, &data_size);

        Entity* n = make_entity<Entity>(pos, glm::vec3(0.0, 0.0, 0.0), asset, data_size);

        entities.push_back(n);

        return n->get_id();
}

void Scene::update() {
        for(Entity* n : entities) {
                n->update();
        }
}
