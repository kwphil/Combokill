#include <glm/glm.hpp>

#include "object.hpp"

std::vector<Object*> object_list = { };

Object::Object(glm::vec3 origin) 
: origin(origin) {
        object_list.push_back(this);
}

Object::Object(const Object& other) {
        origin = other.origin;
        id = other.get_id();
}

