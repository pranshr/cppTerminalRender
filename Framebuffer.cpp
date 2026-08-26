#include "Framebuffer.hpp"
#include <asm-generic/ioctls.h>
#include <iostream>
#include <ostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>


    
Window::Window() { 
    std::cout << "\e[?1049h]";

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &window); 
    width = window.ws_col / 2;
    height = window.ws_row;
    buffer.resize(height, std::vector<char>(width));
}

Window::~Window() {
    std::cout << "\e[?1049l]";
}

int Window::getWidth() {return width;}
int Window::getHeight() {return height;}


void Window::clearBuffer(char fill) {
    buffer.assign(height, std::vector<char>(width, fill));
}

void Window::setPixel(int screenX, int screenY, char c) {
    // Rendered pixel can be out of bounds, so don't render it.
    if (screenX < 0 || screenX >= width || screenY < 0 || screenY >= height) {
        return;
    }

    buffer.at(screenY).at(screenX) = c;
}

void Window::presentBuffer(bool clearSpace) {
    // Reset the screen
    if (clearSpace) {
        for (int i=0; i< height; i++) {
            std::cout << std::endl;
        }
    }
    std::cout << "\033[2J\033[1;1H";

    // Print the buffer
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << buffer.at(i).at(j) << buffer.at(i).at(j);
        }
        std::cout << std::endl;
    }

    std::cout.flush();
}
