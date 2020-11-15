#ifndef GRAPHICS_LIB_H_
#define GRAPHICS_LIB_H_

#include <window.h>
#include <color.h>
#include <matrix_stack.h>
#include <projection.h>
#include <vector2.h>
#include <string>

class Window;

class GraphicsLib
{
public:
    GraphicsLib();
    ~GraphicsLib();
    void create_window(const char title[], uint32_t width, uint32_t height, p_mode_t draw_mode);
    void set_orthographic(double left, double right, double bottom, double top, double near, double far);
    void set_perspective(double fov, double near, double far);
    void set_background_color(float r, float g, float b);
    void plot_point(int x, int y, Color c);
    void draw_line(int x0, int y0, int x1, int y1);
    void draw_triangle(Vector2 point_a, Color color_a, Vector2 point_b, Color color_b, Vector2 point_c, Color color_c);
    Window* window;
    MatrixStack* matrix_stack;
    Projection* projection;
};

#endif //GRAPHICS_LIB_H_
