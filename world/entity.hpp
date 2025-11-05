#pragma once

#include <glm/ext/vector_float3.hpp>

#include "../core/object.hpp"

#define make_entity make_renderable

class Entity : public Renderable {
public:
        // In width, height, and length
        float hitbox_x, hitbox_y, hitbox_z;

        Entity(glm::vec3 origin, glm::vec3 look_at, float* render, size_t render_len) 
        : Renderable(origin, look_at, render, render_len), hitbox_x(0), hitbox_y(0), hitbox_z(0) { }
        virtual void update() { } 
};

class TestEntity : public Entity {
public:
        TestEntity(glm::vec3 origin, glm::vec3 look_at, float* render, size_t render_len)
        : Entity(origin, look_at, render, render_len) { }

        void update() {
                look_at = object_list.at(0)->origin;
        }
};
