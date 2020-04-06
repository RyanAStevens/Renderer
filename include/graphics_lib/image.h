#ifndef IMAGE_H_
#define IMAGE_H_

#include <color.h>
#include <vector>

class Image
{
public:
    Image();
    ~Image();
    std::vector<Color> pixels;
private:
};

#endif //IMAGE_H_
