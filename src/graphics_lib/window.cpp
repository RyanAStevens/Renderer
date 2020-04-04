#include <PixelToaster.h>
#include <image.h>
#include <string.h>

Window::Window()
{
}

Window::Window(std::string title, uint32_t width, uint32_t height)
{
    this->height = height;
    this->width = width;
    this->title = title;
    this->toasted_display = PixelToaster::Display(title, width, height, Output::Fullscreen);
    this->image = Image(width, height);
}

Window::~Window()
{
}

void Window::update()
{
   this->toasted_display.update(this->image)
}

uint32_t Window::open()
{
    return this->toasted_display.open();
}
