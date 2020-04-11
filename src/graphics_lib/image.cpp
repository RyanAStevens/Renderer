#include <image.h>

Image::Image()
{
    //maybe this doesnt need to be a class. Maybe image doesnt need to exist at all...
}

Image::Image(uint32_t width, uint32_t height)
{
    this->width = width;
    this->height = height;
}
