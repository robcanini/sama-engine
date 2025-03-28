#include <vector>
#include <glm/glm.hpp>

using namespace glm;

struct Vertex {
    vec3 position;
};

std::vector<Vertex> generateCircleMesh(float radius = 1.0f, int segments = 32)
{
    std::vector<Vertex> vertices;
    vertices.push_back({ vec3(0.0f, 0.0f, 0.0f) });

    for (int i = 0; i <= segments; ++i)
    {
        float angle = float(i) / segments * 2.0f * 3.1415f; // todo: pi approximated
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        vertices.push_back({ vec3(x, y, 0.0f) });
    }

    return vertices;
}