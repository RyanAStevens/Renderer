#ifndef GRAPHICS_LIB_H_
#define GRAPHICS_LIB_H_

#include <color.h>
#include <matrix_stack.h>
#include <matrix.h>
#include <projection.h>
#include <vector2.h>
#include <vertex.h>
#include <transform_matrix.h>
#include <string>

#define RED_SHIFT 16
#define GREEN_SHIFT 8

class GraphicsLib
{
public:
    GraphicsLib();
    GraphicsLib(p_mode_t draw_mode, int width, int height);
    ~GraphicsLib();
    void set_orthographic(double left, double right, double bottom, double top, double near, double far);
    void set_perspective(double fov, double near, double far);
    void clear_image(Color c);
    void plot_point(uint32_t x, uint32_t y, Color c);
    void draw_line(Vertex vert1, Vertex vert2, Color c);
    void draw_triangle(Vector2 point_a, Color color_a, Vector2 point_b, Color color_b, Vector2 point_c, Color color_c);
    void begin_shape();
    void end_shape();
    void add_vertex(double x, double y, double z);
    void circle(int steps);
    void square();
    void cube();
    void face();
    void faces();
    void persp_initials();
    void face_test();
    void ortho_test();
    void ortho_test_scale();
    void ortho_test_rotate();
    void ortho_cube();
    void ortho_cube2();
    void persp_cube();
    void persp_multi_cubes();
    uint32_t width;
    uint32_t height;
    uint32_t n_pixels;
    uint32_t* image;
    std::vector<Vertex> vertices;
    MatrixStack matrix_stack;
    Projection* projection;
};

#endif //GRAPHICS_LIB_H_
