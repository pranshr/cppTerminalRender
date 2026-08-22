#include "Framebuffer.hpp"
#include <cstdlib>
#include <utility>
#include "Draw.hpp"


void drawRect(int x, int y, int h, int w, Window& window) {
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {
            if ((j > 0 && j < (w-1)) && (i > 0 && i < (h-1))) 
                continue;

            window.setPixel(x+j, y+i);
        }
    }
}

void drawLine(int x1, int y1, int x2, int y2, Window& window) {
    // Using Bressenham's Line Drawing Algorithm
    int a1, b1, a2, b2;
    bool horizontal = std::abs(x2 - x1) > std::abs(y2 - y1); 
    
    if (horizontal) {
      a1 = x1;
      a2 = x2;
      b1 = y1;
      b2 = y2;
    }
    else {
      a1 = y1;
      a2 = y2;
      b1 = x1;
      b2 = x2;
    }

    if (a1 > a2) {
        std::swap(a1, a2);
        std::swap(b1, b2);
    }   

    int db = b2 - b1;
    int da = a2 - a1;

    int dir = (db > 0) ? 1 : -1;
    db *= dir;

    if (da != 0) {
        int b = b1;
        int p = 2*db - da;

        for (int i=0; i<da+1; i++) {
            if (horizontal){
                window.setPixel(a1 + i, b);
            } else {
                window.setPixel(b, a1 + i);
            }

            if (p >= 0) {
                b += dir;
                p -= 2*da;
            }
            p += 2*db;
        }
    }
}
