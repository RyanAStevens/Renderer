#include <PixelToaster.h>
#include <window.h>
#include <string.h>

Window::Window()
{
    printf("hello from  Window default constructor\n");
}

Window::Window(const char title[], uint32_t width, uint32_t height)
{
    printf("hello from  Window non-default constructor\n");
    this->height = height;
    this->width = width;
    this->image = std::vector<PixelToaster::FloatingPointPixel>(width*height);
    this->toasted_display = new PixelToaster::Display(title, width, height, PixelToaster::Output::Fullscreen, PixelToaster::Mode::FloatingPoint);
}

Window::~Window()
{
    delete this->toasted_display;
}

void Window::update()
{
   this->toasted_display->update(this->image);
}

uint32_t Window::open()
{
    return this->toasted_display->open();
}

void Window::listen(Application* app)
{
   this->toasted_display->listener(app);
}
