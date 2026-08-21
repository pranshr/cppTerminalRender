#include "Framebuffer.hpp"
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