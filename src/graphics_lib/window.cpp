#include <PixelToaster.h>
#include <string.h>

Window::Window()
{
}

Window::Window(std::string title, uint32_t width, uint32_t height, uint32_t output_type)
{
    this->window = PixelToaster::Display(title, width, height, output_type);
}

Window::~Window()
{
}
