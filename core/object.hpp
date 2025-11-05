#include <glm/ext/vector_float3.hpp>
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

class Renderable : public Object {
public:
        glm::vec3 look_at;
        float* vertices;
        int vertices_len;

        Renderable(glm::vec3 origin, glm::vec3 look_at, float* vertices, int vertices_len)
        : Object(origin), look_at(look_at), vertices(vertices), vertices_len(vertices_len) { }

        // WARNING: DOES NOT CHECK ALLOCATION SIZE. BE WARNED
        // Expects ptr as the vertices pointer, plus offset
        void render(float* ptr);
};

// Lists Renderables
extern std::vector<Renderable*> render_list;

template <typename T, typename... Args>
T* make_renderable(Args&&... args) {
        T* obj = new T(std::forward<Args>(args)...);
        object_list.push_back(obj);
        render_list.push_back(obj);
        return obj;
}

