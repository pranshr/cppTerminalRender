#include "Framebuffer.hpp"
#include "Draw.hpp"
#include "Math.hpp"
using namespace std;



int main(int argc, char **argv) {
  Window w;
  w.clearBuffer(); // Reset the buffer.
  w.presentBuffer(true); // This first call resets the screen.

  // w.setPixel(50, 15);
  // drawRect(35, 8, 9, 29, w);
  // drawLine(35, 8, 44, 36, w);
  
  vec2 p1 = {15, 18};
  vec2 p2 = {32, 3};
  vec2 p3 = {49, 18};

  drawTriangle(p1, p2, p3, w);
  w.presentBuffer();

  return 0;
}
