#include "Math.hpp"
#include <cmath>
#include <numbers>

namespace {
    float pi = std::numbers::pi_v<float>;
}

void rotateX(vec3 &point, int angle) {
    float y = point.y;
    float z = point.z;
    float cos = std::cos(angle * pi/180);
    float sin = std::sin(angle * pi / 180);

    point.z = (z * cos + y * sin);
    point.y = (y * cos - z * sin);
}

void rotateY(vec3& point, int angle) {
    float x = point.x;
    float z = point.z;
    float cos = std::cos(angle * pi/180);
    float sin = std::sin(angle * pi/180);

    point.x = (x * cos + z * sin);
    point.z = (z * cos - x * sin);
}

void rotateZ(vec3& point, int angle) {
    float x = point.x;
    float y = point.y;
    float cos = std::cos(angle * pi / 180);
    float sin = std::sin(angle * pi / 180);

    point.x = (x * cos - y * sin);
    point.y = (y * cos + x * sin);
}
