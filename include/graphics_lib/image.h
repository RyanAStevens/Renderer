#ifndef IMAGE_H_
#define IMAGE_H_

#include <color.h>
#include <vector>
#include <stdint.h>
#include <PixelToaster.h>

class Image
{
public:
    Image();
    Image(uint32_t width, uint32_t height);
    ~Image();
    std::vector<PixelToaster::FloatingPointPixel> pixels;
private:
    uint32_t width;
    uint32_t height;
};

#endif //IMAGE_H_
