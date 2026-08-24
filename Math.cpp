#include "Math.hpp"
#include <cmath>
#include <numbers>

namespace {
    float pi = std::numbers::pi_v<float>;
}

void rotateX(vec3 &point, int angle) {
    float y = point.y;
    float z = point.z;

    point.z = (z * std::cos(angle * pi/180) + y * sin(angle * pi/180));
    point.y = (y * std::cos(angle * pi/180) - z * sin(angle * pi/180));
}

void rotateY(vec3& point, int angle) {
    float x = point.x;
    float z = point.z;

    point.x = (x * std::cos(angle * pi/180) + z * sin(angle * pi/180));
    point.z = (z * std::cos(angle * pi/180) - x * sin(angle * pi/180));
}

void rotateZ(vec3& point, int angle) {
    float x = point.x;
    float y = point.y;

    point.x = (x * std::cos(angle * pi / 180) - y * sin(angle * pi / 180));
    point.y = (y * std::cos(angle * pi / 180) + x * sin(angle * pi / 180));
}
