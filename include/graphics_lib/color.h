class Color {
public:
    Color();
    Color(double r, double g, double b);
    ~Color();
    float r;
    float g;
    float b;
    Color operator+(const Color& rhs);
    Color operator-(const Color& rhs);
    Color operator*(const Color& rhs);
    Color operator*(const double scalar);
    Color operator/(const double scalar);
};

