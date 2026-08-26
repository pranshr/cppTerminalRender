#include "Framebuffer.hpp"
#include "Math.hpp"
#include <cstdlib>
#include <utility>
#include "Draw.hpp"

namespace {
    void fillFlatBottomTriangle(vec2 points[3], Window& window) {
        float x1 = points[0].x;
        float x2 = points[0].x;

        float invSlope1 = (float)(points[1].x - points[0].x)/(float)(points[1].y-points[0].y);
        float invSlope2 = (float)(points[2].x - points[0].x)/(float)(points[2].y-points[0].y);

        for (int y=points[0].y; y <= points[2].y; y++) {
            drawLine(x1, y, x2, y, window);

            x1 += invSlope1;
            x2 += invSlope2;
        }
    }

    void fillFlatTopTriangle(vec2 points[3], Window& window) {
        float x1 = points[2].x;
        float x2 = points[2].x;

        float invSlope1 = (float)(points[2].x - points[0].x)/(float)(points[2].y - points[0].y);
        float invSlope2 = (float)(points[2].x - points[1].x)/(float)(points[2].y - points[1].y);

        for (int y = points[2].y; y >= points[0].y; y--) {
            drawLine(x1, y, x2, y, window);

            x1 -= invSlope1;
            x2 -= invSlope2;
        }
    }

    float cameraZDistance = 30.0f;
    float f = 20.0f; 

    vec2 project3DTo2D(vec3 point, Window& window) {

        return vec2{
            ((float)window.getWidth()/2) + (point.x / (cameraZDistance - point.z) * f),
            ((float)window.getHeight()/2) + (point.y / (cameraZDistance - point.z) * f),
        };
    }
}


void drawRect(int x, int y, int h, int w, Window& window) {
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {
            if ((j > 0 && j < (w-1)) && (i > 0 && i < (h-1))) {
              continue;
            }

            window.setPixel(x+j, y+i);
        }
    }
}

void drawLine(int x1, int y1, int x2, int y2, Window& window) {
    // Using Bressenham's Line Drawing Algorithm
    bool horizontal = std::abs(x2 - x1) >= std::abs(y2 - y1); 
    
    int a1 = horizontal ? x1 : y1;
    int b1 = horizontal ? y1 : x1;
    int a2 = horizontal ? x2 : y2;
    int b2 = horizontal ? y2 : x2;

    if (a1 > a2) {
        std::swap(a1, a2);
        std::swap(b1, b2);
    }   

    int da = a2 - a1;
    int db = b2 - b1;
    int dir = (db > 0) ? 1 : -1;
    db *= dir;

    if (da != 0) {
        int b = b1;
        int p = 2*db - da;

        for (int a = a1; a <= a2; a++) {
            if (horizontal){
                window.setPixel(a, b);
            } else {
                window.setPixel(b, a);
            }

            if (p >= 0) {
                b += dir;
                p -= 2*da;
            }
            p += 2*db;
        }
    }
}

void drawWireframeTriangle(triangle2D triangle, Window &window) {
    vec2 a = triangle.a;
    vec2 b = triangle.b;
    vec2 c = triangle.c;

    drawLine(a.x, a.y, b.x, b.y, window);
    drawLine(b.x, b.y, c.x, c.y, window);
    drawLine(c.x, c.y, a.x, a.y, window);
}

void drawTriangle(triangle2D triangle, Window &window) {
    // 1. Sort points in increasing order of y and find midpoint
    // 2. Rasterize the top tringle
    // 3. Rasterize the bottom triangle
    vec2 a = triangle.a;
    vec2 b = triangle.b;
    vec2 c = triangle.c;
    vec2 m;
    
    if (a.y > b.y) std::swap(a, b);
    if (a.y > c.y) std::swap(a, c);
    if (b.y > c.y) std::swap(b, c);

    if (a.y == b.y) {
        // Draw flat top triangle
        vec2 flatTopTriangle[3] = {a, b, c};
        fillFlatTopTriangle(flatTopTriangle, window);
    } else if (a.y == c.y) {
        // Draw flat bottom traingle
        vec2 flatBottomTriangle[3] = {a, b, c};
        fillFlatBottomTriangle(flatBottomTriangle, window);
    } else {
        // Find midpoint.
        vec2 m;
        m.y = b.y;
        m.x = ((float)((c.x - a.x)*(b.y - a.y))/(float)(c.y - a.y)) + a.x;

        vec2 flatBottomTriangle[3] = {a, b, m};
        vec2 flatTopTriangle[3] = {b, m, c};

        fillFlatBottomTriangle(flatBottomTriangle, window);
        fillFlatTopTriangle(flatTopTriangle, window);
    }
}

void renderTriangle(triangle3D triangle, Window& window) {
  triangle2D transformedTriangle{
      project3DTo2D(triangle.a, window),
      project3DTo2D(triangle.b, window),
      project3DTo2D(triangle.c, window),
  };

  drawTriangle(transformedTriangle, window);
}

void renderWireframeTriangle(triangle3D triangle, Window &window) {
  triangle2D transformedTriangle{
      project3DTo2D(triangle.a, window),
      project3DTo2D(triangle.b, window),
      project3DTo2D(triangle.c, window),
  };

  drawWireframeTriangle(transformedTriangle, window);
}

void renderPoint(vec3 point, Window &window) {
    vec2 point2D = project3DTo2D(point, window);
    window.setPixel(point2D.x, point2D.y);
}

void renderLine(vec3 start, vec3 end, Window &window) {
    vec2 start2D = project3DTo2D(start, window);
    vec2 end2D = project3DTo2D(end, window);

    drawLine(start2D.x, start2D.y, end2D.x, end2D.y, window);
}
