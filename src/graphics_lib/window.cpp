#include <window.h>
#include <PixelToaster.h>
#include <image.h>
#include <string.h>

Window::Window()
{
}

Window::Window(const char title[], uint32_t width, uint32_t height)
{
    this->height = height;
    this->width = width;
    this->toasted_display = PixelToaster::Display(title, width, height, PixelToaster::Output::Fullscreen, PixelToaster::Mode::FloatingPoint);
    this->image = Image(width, height);
}

Window::~Window()
{
}

void Window::update()
{
   this->toasted_display.update(this->image.pixels);
}

uint32_t Window::open()
{
    return this->toasted_display.open();
}
