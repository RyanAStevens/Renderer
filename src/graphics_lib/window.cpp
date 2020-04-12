#include <PixelToaster.h>
#include <window.h>
#include <string.h>

Window::Window()
{
}

Window::Window(const char title[], uint32_t width, uint32_t height)
{
    printf("hello from Window constructor\n");
    this->height = height;
    this->width = width;
    this->pixels = std::vector<PixelToaster::FloatingPointPixel>(width*height);
    printf("pixels size = %d\n", this->pixels.size());
    this->toasted_display = new PixelToaster::Display(title, width, height, PixelToaster::Output::Fullscreen, PixelToaster::Mode::FloatingPoint);
    printf("goodbye from Window constructor\n");
}

Window::~Window()
{
    printf("hello from Window destructor\n");
    delete this->toasted_display;
}

void Window::update()
{
   this->toasted_display->update(pixels);
}

uint32_t Window::open()
{
    printf("Window::open 1\n");
    return this->toasted_display->open();
}
