#include <image.h>
#include <window.h>
#include <matrix_stack.h>
#include <projection.h>

class GraphicsLib
{
public:
    GraphicsLib();
    ~GraphicsLib();
    void set_background_color(float r, float g, float b);
    void plot_point(int x, int y, Color c);
    void draw_line(int x0, int y0, int x1, int y1);
    void draw_triangle(Vector2 point_a, Color color_a, Vector2 point_b, Color color_b, Vector2 point_c, Color color_c);

private:
    Image image;
    Window window;
    MatrixStack matrix_stack;
    Projection projection;
}
