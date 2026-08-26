#include "Framebuffer.hpp"
#include "Draw.hpp"
#include "Math.hpp"
#include <chrono>
#include <string>
#include <thread>
#include <vector>
using namespace std;



int main(int argc, char **argv) {
  Window w;
  w.clearBuffer(); // Reset the buffer.
  w.presentBuffer(true); // This first call resets the screen.
  
  using clock = std::chrono::steady_clock;
  constexpr auto frameTime = std::chrono::milliseconds(500);
  auto nextFrame = clock::now();

  // w.setPixel(50, 15);
  // drawRect(35, 8, 9, 29, w);
  // drawLine(35, 8, 44, 36, w);

  // triangle3D tri = {
  //   {-11.54, -10, 0},
  //   {11.54, -10, 0},
  //   {0, 10, 0}
  // };

  Mesh square ={ 
    {
      {-12, -12, 6},
      {12, -12, 6},
      {12, 12, 6},
      {-12, 12, 6},
    },
    {
      {0, 1, 2},
      {0, 2, 3}, 
    }
  };

  // triangle3D square[12] {
  //   {pts[0], pts[1], pts[2]},
  //   {pts[0], pts[2], pts[3]},
  // };

  int angle = 0;

  while (angle <= 360) {
    nextFrame += frameTime;
    w.clearBuffer();

    for (Triangle face : square.faces) {
      triangle3D tri = {
        square.vertices[face.a],
        square.vertices[face.b],
        square.vertices[face.c],
      };

      rotateX(tri.a, angle);
      rotateX(tri.b, angle);
      rotateX(tri.c, angle);

      renderTriangle(tri, w);
    }

    string debug = to_string(angle) + "deg ";
    for (int i=0; i<debug.length(); i++) {
      w.setPixel(i, w.getHeight()-1, debug.at(i));
    }

    w.presentBuffer();
    angle += 10;

    std::this_thread::sleep_until(nextFrame);
  }

  return 0;
}
