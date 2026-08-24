#include "Framebuffer.hpp"
#include "Draw.hpp"
#include "Math.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
using namespace std;



int main(int argc, char **argv) {
  ofstream outFile("../local/tricoords.txt");
  if (!outFile.is_open()) {
    cerr << "Error opening file" << endl;
    return 1;
  }

  Window w;
  w.clearBuffer(); // Reset the buffer.
  w.presentBuffer(true); // This first call resets the screen.
  using clock = std::chrono::steady_clock;
  // constexpr auto frameTime = std::chrono::microseconds(16667);
  constexpr auto frameTime = std::chrono::milliseconds(500);
  auto nextFrame = clock::now();

  // w.setPixel(50, 15);
  // drawRect(35, 8, 9, 29, w);
  // drawLine(35, 8, 44, 36, w);

  triangle3D tri = {
    {-11.54, -10, 0},
    {11.54, -10, 0},
    {0, 10, 0}
  };

  int angle = 0;

  while (angle <= 360) {
    nextFrame += frameTime;

    w.clearBuffer();
    // renderLine({0, 0, 0}, {10, 0, 0}, w);
    // renderLine({0, 0, 0}, {0, 10, 0}, w);
    // renderLine({0, 0, 0}, {0, 0, 10}, w);

    triangle3D copy = tri;
    rotateY(copy.a, angle);
    rotateY(copy.b, angle);
    rotateY(copy.c, angle);

    // outFile << "{" << copy.a.x << " " << copy.a.y << " " << copy.a.z << "}  "
    //         << "{" << copy.b.x << " " << copy.b.y << " " << copy.b.z << "}  "
    //         << "{" << copy.c.x << " " << copy.c.y << " " << copy.c.z << "}  "
    //         << endl
    // ;

    renderTriangle(copy, w);

    string debug = to_string(angle) + "deg ";
    for (int i=0; i<debug.length(); i++) {
      w.setPixel(i, w.getHeight()-1, debug.at(i));
    }

    w.presentBuffer();
    angle += 10;

    std::this_thread::sleep_until(nextFrame);
  }
  outFile.close();

  return 0;
}
