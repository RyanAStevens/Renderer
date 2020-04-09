#ifndef WINDOW_H_
#define WINDOW_H_

#include <PixelToaster.h>
#include <string>
#include <stdint.h>
#include <window.h>
#include <image.h>

class Window
{
public:
    Window();
    Window(std::string title, uint32_t width, uint32_t height);
    ~Window();
 
    uint32_t open();
    void update();
    std::string title;
    uint32_t height;
    uint32_t width;
    Image image;
    PixelToaster::Display toasted_display;
};

#endif //WINDOW_H_
