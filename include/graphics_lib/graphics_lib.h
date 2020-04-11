#ifndef GRAPHICS_LIB_H_
#define GRAPHICS_LIB_H_

#include <image.h>
#include <window.h>
#include <matrix_stack.h>
#include <projection.h>
#include <vector2.h>
#include <string>

class GraphicsLib
{
public:
    GraphicsLib();
    ~GraphicsLib();
    void create_window(const char title[], uint32_t width, uint32_t height);
    void set_background_color(float r, float g, float b);
    void plot_point(int x, int y, Color c);
    void draw_line(int x0, int y0, int x1, int y1);
    void draw_triangle(Vector2 point_a, Color color_a, Vector2 point_b, Color color_b, Vector2 point_c, Color color_c);
    Window window;
    MatrixStack matrix_stack;
    Projection projection;
};

#endif //GRAPHICS_LIB_H_
