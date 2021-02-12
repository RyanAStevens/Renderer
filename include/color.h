#ifndef COLOR_H_
#define COLOR_H_

class Color {
public:
    Color();
    Color(double r, double g, double b);
    ~Color();
    float r;
    float g;
    float b;
    void print();
    Color operator+(const Color& rhs);
    Color operator-(const Color& rhs);
    Color operator*(const Color& rhs);
    Color operator*(const double scalar);
    Color operator/(const double scalar);
};

#endif //COLOR_H_
