#ifndef GRAPHICS_LIB_H_
#define GRAPHICS_LIB_H_

#include <color.h>
#include <matrix_stack.h>
#include <transform_matrix.h>
#include <projection.h>
#include <vector2.h>
#include <vertex.h>
#include <string>
#include <cstddef>

#define RED_SHIFT 16
#define GREEN_SHIFT 8

enum render_status
{
    RENDER_FUNC_SUCCESS = 0,
    RENDER_FUNC_ERROR = -1
};

class GraphicsLib
{
public:
    GraphicsLib();
    GraphicsLib(p_mode_t draw_mode, int width, int height);
    ~GraphicsLib();
    void clear_image(Color c);
    void plot_point(uint32_t x, uint32_t y, Color c);
    void draw_line(Vertex vert1, Vertex vert2, Color c);
    void draw_triangle(Vector2 point_a, Color color_a, Vector2 point_b, Color color_b, Vector2 point_c, Color color_c);
    void begin_shape();
    void end_shape();
    void add_vertex(double x, double y, double z);
    void initialize();
    void print_ctm();
    TransformMatrix& get_ctm();
    void translate(float x,float y,float z);
    void scale(float x,float y,float z);
    void rotate_x(float theta);
    void rotate_y(float theta);
    void rotate_z(float theta);
    void push_matrix();
    void pop_matrix();
    int32_t size();
    uint32_t width;
    uint32_t height;
    uint32_t n_pixels;
    uint32_t* image;
    std::vector<Vertex> vertices;
    MatrixStack matrix_stack;
    Projection* projection;
    TransformMatrix* view;
};

#endif //GRAPHICS_LIB_H_
