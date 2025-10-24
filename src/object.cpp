#include <cstdlib>

#include <glm/glm.hpp>

#include "object.hpp"
#include "etc.h"

std::vector<Object*> object_list = { };
std::vector<Renderable*> render_list = { };

Object::Object(glm::vec3 origin) 
: origin(origin) {
        object_list.push_back(this);
}

Object::Object(const Object& other) {
        origin = other.origin;
        id = other.get_id();
}

void Renderable::render(float* ptr) {
        for(int i = 0; i < vertices_len/3; i++) {
                glm::vec3 new_vertices = glm::vec3(vertices[i], vertices[i+1], vertices[i+2]) + origin;
                
                ptr[i] = new_vertices.x;
                ptr[i+1] = new_vertices.y;
                ptr[i+2] = new_vertices.z;
        }
}

EXTERN_C size_t render(float* list, size_t size) {
        size_t required_size = 0;

        // Am not worried about speed right now
        for(auto curr : render_list) {
                required_size += curr->vertices_len;
        }

        if(size < required_size) {
                realloc(list, required_size*sizeof(float));
        }

        for(int i = 0; i < required_size; i++) {
                render_list[i]->render(list+i);               
        }

        return required_size > size ? required_size : size;
}


