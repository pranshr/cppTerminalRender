#include "Framebuffer.hpp"
#include "Draw.hpp"
using namespace std;



int main(int argc, char **argv) {
  Window w;
  w.clearBuffer(); // Reset the buffer.
  w.presentBuffer(true); // This first call resets the screen.

  
  // drawing a pixel
  // w.setPixel(50, 15);
  // w.presentBuffer();
  drawRect(35, 8, 9, 29, w);
  w.presentBuffer();

  return 0;
}
