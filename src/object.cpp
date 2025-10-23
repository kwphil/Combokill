#include <cstdio>
#include <glm/glm.hpp>

#include "object.hpp"

std::vector<Object> object_list = { };

Object::Object(float* render_data, glm::vec3 origin)
: render_data(render_data), origin(origin) {
        object_list.push_back(*this);
}

Object::Object(const Object& other) {
       render_data = other.render_data;
       origin = other.origin;
       id = other.id;
}

