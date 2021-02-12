#include <color.h>
#include <stdio.h>

Color::Color()
{
//  std::cout << "Hello from default Color constructor\n";    
}

Color::~Color()
{
//  std::cout << "Hello from Color destructor\n"; 
}

Color::Color(double r, double g, double b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

Color Color::operator+(const Color& rhs)
{
    return Color(this->r + rhs.r,
                   this->g + rhs.g,
                   this->b + rhs.b);
}

Color Color::operator-(const Color& rhs)
{
    return Color(this->r - rhs.r,
                   this->g - rhs.g,
                   this->b - rhs.b);
}

Color Color::operator*(const Color& rhs)
{
    return Color(this->r * rhs.r,
                   this->g * rhs.g,
                   this->b * rhs.b);
}

//scalar multiplication
Color Color::operator*(const double scalar)
{
    return Color(this->r * scalar,
                   this->g * scalar,
                   this->b * scalar);
}

//scalar division 
Color Color::operator/(const double scalar)
{
    return Color(this->r / scalar,
                   this->g / scalar,
                   this->b / scalar);
}

void Color::print()
{
   printf("Color: r %f g %f b %f\n", this->r, this->g, this->b); 
}
