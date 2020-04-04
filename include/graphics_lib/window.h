#include <PixelToaster.h>
#include <string.h>

class Window
{
    Window();
    Window(std::string title, uint32_t width, uint32_t height, uint32_t output_type);
    ~Window();
    
    PixelToaster::Display window;
}
