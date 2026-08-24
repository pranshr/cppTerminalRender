#ifndef MATH_HPP
#define MATH_HPP

struct vec2 {
    float x;
    float y;
};

struct vec3 {
    float x;
    float y;
    float z;
};

struct triangle2D {
    vec2 a, b, c;
};

struct triangle3D {
    vec3 a, b, c;
};

void rotateX(vec3& point, int angle);
void rotateY(vec3& point, int angle);
void rotateZ(vec3& point, int angle);

#endif