#ifndef WINDOW_H_
#define WINDOW_H_

#include <PixelToaster.h>
#include <string>
#include <stdint.h>

class Window
{
public:
    Window();
    Window(const char title[], uint32_t width, uint32_t height);
    ~Window();
 
    uint32_t open();
    void update();
    uint32_t height;
    uint32_t width;
    PixelToaster::Display* toasted_display;
    std::vector<PixelToaster::FloatingPointPixel> pixels;
};

#endif //WINDOW_H_
