#include <glm/glm.hpp>

class Object {
private:
        float* render_data;
        glm::vec3 origin;
        uint id;

public:
        Object(float* render_data, glm::vec3 origin); 
        Object(const Object& other);
        glm::vec3 get_origin() { return origin; }
};

// TODO: This is gonna be inefficient. 
// Might want to replace this with a proper allocator 
extern std::vector<Object> object_list;              
