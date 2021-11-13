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

#define TOP_BIT    0x80
#define BOTTOM_BIT 0x40
#define RIGHT_BIT  0x20
#define LEFT_BIT   0x10
#define NEAR_BIT   0x08
#define FAR_BIT    0x04

class GraphicsLib
{
public:
    GraphicsLib();
    GraphicsLib(p_mode_t draw_mode, int width, int height);
    ~GraphicsLib();

    enum perform_clip {
		NO_CLIP,
    	CLIP
    };

    void clear_image(Color c);
    void plot_point(uint32_t x, uint32_t y, Color c);
    void draw_line(Vertex vert1, Vertex vert2, Color c);
    void draw_triangle(Vector2 point_a, Color color_a, Vector2 point_b, Color color_b, Vector2 point_c, Color color_c);
    void set_draw_color(Color c);
    void set_view(Vector3 e, Vector3 g, Vector3 t);
    uint8_t compute_out_code(Vertex v);
    void cohen_sutherland_line_clip_and_draw(Vertex v1, Vertex v2);
    void begin_shape();
    void end_shape(bool perf_clip);
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
    float m_red;
    float m_green;
    float m_blue;
    uint32_t width;
    uint32_t height;
    uint32_t n_pixels;
    uint32_t* image;
    std::vector<Vertex> vertices;
    MatrixStack matrix_stack;
    Projection* projection;
    TransformMatrix* m_window;
    TransformMatrix* m_view;
};

#endif //GRAPHICS_LIB_H_
