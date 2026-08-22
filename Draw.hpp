#ifndef DRAW_HPP
#define DRAW_HPP

#include "Framebuffer.hpp"
#include "Math.hpp"

void drawRect(int x, int y, int h, int w, Window& window);
void drawLine(int x1, int y1, int x2, int y2, Window& window);
void drawTriangle(vec2 a, vec2 b, vec2 c, Window& window);

#endif