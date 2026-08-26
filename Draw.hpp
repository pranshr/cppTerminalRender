#ifndef DRAW_HPP
#define DRAW_HPP

#include "Framebuffer.hpp"
#include "Math.hpp"

void drawRect(int x, int y, int h, int w, Window& window);
void drawLine(int x1, int y1, int x2, int y2, Window& window);
void drawWireframeTriangle(triangle2D triangle, Window& window);
void drawTriangle(triangle2D triangle, Window& window);
void renderTriangle(triangle3D triangle, Window &window);
void renderWireframeTriangle(triangle3D triangle, Window &window);
void renderPoint(vec3 point, Window& window);
void renderLine(vec3 start, vec3 end, Window &window);

#endif