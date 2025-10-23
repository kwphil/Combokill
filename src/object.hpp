#include <glm/glm.hpp>

#pragma once

class Object {
private:
        uint id;

public:
        glm::vec3 origin;

        Object(glm::vec3 origin); 
        Object(const Object& other);
        const uint get_id() const { return id; }
};

// TODO: This is gonna be inefficient. 
// Might want to replace this with a proper allocator 
extern std::vector<Object*> object_list;              

// Ex. make_object<Camera>(
//     glm::vec3(0.0, 0.0, 5.0),
//     glm::vec3(0.0, 1.0, 0.0)
// )
template <typename T, typename... Args>
T* make_object(Args&&... args) {
    T* obj = new T(std::forward<Args>(args)...);
    object_list.push_back(obj);
    return obj;
}

