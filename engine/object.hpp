#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>

#pragma once

/// @brief A basic object
class Object {
private:
        uint id;

public:
        /// @brief the location of the object in world space
        glm::vec3 origin;

        Object(glm::vec3 origin); 
        Object(const Object& other);
        /// @brief Return the id
        const uint get_id() const { return id; }
};

// TODO: This is gonna be inefficient. 
// Might want to replace this with a proper allocator 
/// @brief A list of all objects used
extern std::vector<Object*> object_list;              

/// @brief A factory to make an object
/// Ex. make_object<Camera>(
///     glm::vec3(0.0, 0.0, 5.0),
///     glm::vec3(0.0, 1.0, 0.0)
/// )
template <typename T, typename... Args>
T* make_object(Args&&... args) {
        T* obj = new T(std::forward<Args>(args)...);
        object_list.push_back(obj);
        return obj;
}

/// @brief An object that can be rendered
class Renderable : public Object {
public:
        /// @brief the raw data of the render data
        float* vertices;
        /// @brief the length of the raw data
        int vertices_len;

        Renderable(glm::vec3 origin, float* vertices, int vertices_len)
        : Object(origin), vertices(vertices), vertices_len(vertices_len) { }

        /// @brief A call to be rendered. Best to leave this alone, it's already used
        /// WARNING: DOES NOT CHECK ALLOCATION SIZE. BE WARNED
        /// @param ptr the vertices pointer, plus offset
        void render(float* ptr);
};

/// @brief Lists Renderables
extern std::vector<Renderable*> render_list;

/// @brief Factory to make renderables
template <typename T, typename... Args>
T* make_renderable(Args&&... args) {
        T* obj = new T(std::forward<Args>(args)...);
        object_list.push_back(obj);
        render_list.push_back(obj);
        return obj;
}

