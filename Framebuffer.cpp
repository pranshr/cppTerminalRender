#include "Framebuffer.hpp"
#include <asm-generic/ioctls.h>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>


    
Window::Window() { 
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window); 
    width = window.ws_col;
    height = window.ws_row;
    buffer.resize(height, std::vector<char>(width));
}

int Window::getWidth() {return width;}
int Window::getHeight() {return height;}


void Window::clearBuffer(char fill) {
    buffer.assign(height, std::vector<char>(width, fill));
}

void Window::setPixel(int screenX, int screenY, char c) {
    // Rendered pixel can be out of bounds, so don't render it.
    if (screenX < 0 || screenX > width || screenY < 0 || screenY > height) {
        return;
    }

    buffer.at(screenY).at(screenX) = c;
}

void Window::presentBuffer(bool clearSpace) {
    // Reset the screen
    if (clearSpace) std::cout << "\033[2J\033[1;1H";

    // Print the buffer
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << buffer.at(i).at(j);
        }
    }
}
