#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <asm-generic/ioctls.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>


class Window {
    private:
        struct winsize window;
        int width, height;
        std::vector<std::vector<char>> buffer;
    
    public:
        Window();
        ~Window();

        int getWidth();
        int getHeight();

        void clearBuffer(char fill=' ');
        void setPixel(int screenX, int screenY, char c='#');
        void presentBuffer(bool clearSpace=false);

};

#endif