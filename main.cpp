#include "Framebuffer.hpp"
using namespace std;



int main(int argc, char **argv) {
  Window w;
  w.clearBuffer(); // Reset the buffer.
  w.presentBuffer(true); // This first call resets the screen.

  
  // drawing a pixel
  w.setPixel(50, 15);
  w.presentBuffer();

  return 0;
}
