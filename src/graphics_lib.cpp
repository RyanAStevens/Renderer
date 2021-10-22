#include <graphics_lib.h>   
#include <vector2.h>
#include <color.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <limits>

#include <stack_trace.h>

GraphicsLib::GraphicsLib(p_mode_t draw_mode, int w, int h) : 
    m_red(0.0),
    m_green(0.0),
    m_blue(0.0)
{
    width = w;
    height = h;
    n_pixels = w * h;

    image = new uint32_t[n_pixels];
    
    //create windowing matrix
    m_window = new TransformMatrix(IDENTITY);
    *m_window = TransformMatrix(TRANSLATE, (w-1)/2, (h-1)/2, 0) * TransformMatrix(SCALE, w/2, h/2, 0) * TransformMatrix(INVERT_Y);
   
    projection = new Projection(draw_mode, width, height);

    m_view = new TransformMatrix();
    set_view(Vector3(0,0,0), Vector3(0,0,-1), Vector3(0,1,0));
}

GraphicsLib::~GraphicsLib()
{
    printf("hello from GraphicsLib destructor\n");
}

void GraphicsLib::set_draw_color(Color c)
{
    m_red = c.r;
    m_green = c.g;
    m_blue = c.b;
}

void GraphicsLib::set_view(Vector3 eye, Vector3 gaze, Vector3 view_up)
{
    TransformMatrix m_trans(TRANSLATE, -1.0*eye.get_i(), -1.0*eye.get_j(), -1.0*eye.get_k());
    TransformMatrix m_basis;

    Vector3 w;
    Vector3 u;
    Vector3 v;

    w = (gaze * -1.0) / gaze.mag();
    u = view_up.cross(w) / (view_up.cross(w)).mag();
    v = w.cross(u);
    
    (*m_basis.data)[0][0] = u.get_i();
    (*m_basis.data)[0][1] = u.get_j();
    (*m_basis.data)[0][2] = u.get_k();

    (*m_basis.data)[1][0] = v.get_i();
    (*m_basis.data)[1][1] = v.get_j();
    (*m_basis.data)[1][2] = v.get_k();

    (*m_basis.data)[2][0] = w.get_i();
    (*m_basis.data)[2][1] = w.get_j();
    (*m_basis.data)[2][2] = w.get_k();

    if(NULL == m_view)
    {
        m_view = new TransformMatrix();
    }

    *m_view = m_basis * m_trans;
}

void GraphicsLib::clear_image(Color c)
{
    uint32_t pixel_color = uint8_t(c.r * 255) << RED_SHIFT | uint8_t(c.g * 255) << GREEN_SHIFT | uint8_t(c.b * 255);
	for (uint32_t i = 0; i < height * width; i++)
	{
        image[i] = pixel_color;
	}
}


void GraphicsLib::begin_shape()
{
    //initialize point array
    vertices.clear();
}

//clipping in 3D requires a 6bit outcode. highest 2 bits are not used
uint8_t GraphicsLib::compute_out_code(Vertex v)
{
	uint8_t ret = 0;

    //y axis
    if(v.y() > projection->top)
    {
    	ret |= TOP_BIT;
    }
    else if(v.y() < projection->bottom)
    {
    	ret |= BOTTOM_BIT;
    }

    //x axis
    if(v.y() > projection->right)
    {
    	ret |= RIGHT_BIT;
    }
    else if(v.y() < projection->left)
    {
    	ret |= LEFT_BIT;
    }

    //z axis
    if(v.y() > projection->near)
    {
    	ret |= NEAR_BIT;
    }
    else if(v.y() < projection->far)
    {
    	ret |= FAR_BIT;
    }

    return ret;
}

void GraphicsLib::cohen_sutherland_line_clip_and_draw(Vertex v1, Vertex v2)
{
    printf("hello from cohen_sutherland_line_clip_and_draw\n");
    bool accepted = false;
    bool done = false;

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    uint8_t ocOut = 0;
    uint8_t oc1 = compute_out_code(v1);
    uint8_t oc2 = compute_out_code(v2);
    TransformMatrix ctm = get_ctm();
    v1.print();
    v2.print();
    printf("oc1: %x oc2: %x\n", oc1, oc2);
    printf("oc1 & oc2: %x\n", oc1 & oc2);

    while(!done)
    {
        if(0 == oc1 && 0 == oc2)
        {
            //trivial accept
            printf("trivial accepted line\n");
            accepted = true;
            done = true;
        }
        else if(0 != (oc1 & oc2))
        {
            //trivial reject
            printf("trivial rejected line\n");
            done = true;
        }
        else
        {
            //start clipping
            if(0 != oc1)
            {
                //v1 is outside
                ocOut = oc1;
            }
            else
            {
                //v2 is outside
                ocOut = oc2;
            }

            //find intersection
            if(ocOut & TOP_BIT)
            {
                x = v1.x() + (v2.x() - v1.x()) * (projection->top - v1.y()) / (v2.y() - v1.y());
                y = projection->top;
                z = v1.z() + (v2.z() - v1.z()) * (projection->top - v1.y()) / (v2.y() - v1.y());
            }
            else if(ocOut & BOTTOM_BIT)
            {
                x = v1.x() + (v2.x() - v1.x()) * (projection->bottom - v1.y()) / (v2.y() - v1.y());
                y = projection->bottom;
                z = v1.z() + (v2.z() - v1.z()) * (projection->bottom - v1.y()) / (v2.y() - v1.y());
            }
            else if(ocOut & RIGHT_BIT)
            {
                x = projection->right;
                y = v1.y() + (v2.y() - v1.y()) * (projection->right - v1.x()) / (v2.x() - v1.x());
                z = v1.z() + (v2.z() - v1.z()) * (projection->right - v1.x()) / (v2.x() - v1.x());
            }
            else if(ocOut & LEFT_BIT)
            {
                x = projection->left;
                y = v1.y() + (v2.y() - v1.y()) * (projection->left - v1.x()) / (v2.x() - v1.x());
                z = v1.z() + (v2.z() - v1.z()) * (projection->left - v1.x()) / (v2.x() - v1.x());
            }
            else if(ocOut & NEAR_BIT)
            {
                x = v1.x() + (v2.x() - v1.x()) * (projection->near - v1.z()) / (v2.z() - v1.z());
                y = v1.y() + (v2.y() - v1.y()) * (projection->near - v1.z()) / (v2.z() - v1.z());
                z = projection->near;
            }
            else if(ocOut & FAR_BIT)
            {
                x = v1.x() + (v2.x() - v1.x()) * (projection->far - v1.z()) / (v2.z() - v1.z());
                y = v1.y() + (v2.y() - v1.y()) * (projection->far - v1.z()) / (v2.z() - v1.z());
                z = projection->far;
            }

            //move outside point to intersection
            if(ocOut == oc1)
            {
                v1 = Vertex(x, y, z);
                oc1 = compute_out_code(v1);
            }
            else
            {
                v2 = Vertex(x, y, z);
                oc2 = compute_out_code(v2);
            }
            printf("clipped line: (%f, %f, %f)\n", x, y, z);
        }
    }

    if(accepted)
    {
        v1 = *m_window * *(projection->matrix) * *m_view * ctm * v1;
        v2 = *m_window * *(projection->matrix) * *m_view * ctm * v2;
        //draw the line
        draw_line(v1, v2, Color(m_red, m_green, m_blue));

    } 
}

void GraphicsLib::end_shape()
{
    //draw the shape
    for(int i = 0; i < vertices.size(); i += 2)
    {
        //apply current transformation
        Vertex vert1 = vertices[i];
        Vertex vert2 = vertices[i+1];
        //perform clipping operation here  
        
        //clip and draw line
        cohen_sutherland_line_clip_and_draw(vert1, vert2);
    }
    //projection->matrix->print();
}

void GraphicsLib::draw_line(Vertex vert1, Vertex vert2, Color c)
{   
    
    double m = 0;
    double x_f = 0;
    double y_f = 0;
    double t = 0.0f;

    //homogenize
    double x0 = vert1.x() / vert1.h();
    double y0 = vert1.y() / vert1.h();
    double x1 = vert2.x() / vert2.h();
    double y1 = vert2.y() / vert2.h();
    
    //calculate slope
    if(x0 == x1)
    {
        //vertical line, infinite slope
        m = std::numeric_limits<double>::max();
    }
    else
    {
        m = (y1 - y0) / (x1 - x0);
    }
    
    if(m <= 1 && m >= -1)
    {
        //swap order if needed
        if(x1 < x0)
        {
            double x1_tmp = x1;
            double y1_tmp = y1;
            x1 = x0;
            y1 = y0;
            x0 = x1_tmp;
            y0 = y1_tmp;
        }

        for(double x = x0; x <= x1; x++)
        {
            t = (x - x0) / (x1 - x0); 
            y_f = y0 + ((y1 - y0) * t);
            plot_point(int(x), int(y_f), c);
        }
    }
    else
    {
        //swap order if needed
        if(y1 < y0)
        {
            double x1_tmp = x1;
            double y1_tmp = y1;
            x1 = x0;
            y1 = y0;
            x0 = x1_tmp;
            y0 = y1_tmp;
        }
       
        for(double y = y0; y <= y1; y++)
        {
            t = (y - y0) / (y1 - y0); 
            x_f = x0 + ((x1 - x0) * t);
            plot_point(int(x_f), int(y), c);
        }
    }
}

void GraphicsLib::plot_point(uint32_t x, uint32_t y, Color c)
{
	uint32_t index = (y * width) + x;
    uint32_t pixel_color = uint8_t(c.r * 255) << RED_SHIFT | uint8_t(c.g * 255) << GREEN_SHIFT | uint8_t(c.b * 255);
	//ensure index is within bounds of the image vector
	if( index >= 0 && index < width * height)
	{
        //printf("plot_point: (%u, %u) index=%u pixel_color=%u\n", x, y, index, pixel_color);
        image[index] = pixel_color;
	}
	else
	{
		//printf("plot_point: ERROR point (%d, %d) is out of bounds for the current window\n", x, y);
	}
}

void GraphicsLib::add_vertex(double x_in, double y_in, double z_in)
{
    Vertex v(x_in, y_in, z_in);
    vertices.push_back(v);
}

void GraphicsLib::initialize()
{
   matrix_stack.initialize();
}

void GraphicsLib::print_ctm()
{
   matrix_stack.print_ctm();
}

void GraphicsLib::translate(float x,float y,float z)
{
   matrix_stack.translate(x, y, z);
}

void GraphicsLib::scale(float x,float y,float z)
{
   matrix_stack.scale(x, y, z);
}

void GraphicsLib::rotate_x(float theta)
{
   matrix_stack.rotate_x(theta);
}

void GraphicsLib::rotate_y(float theta)
{
   matrix_stack.rotate_y(theta);
}

void GraphicsLib::rotate_z(float theta)
{
   matrix_stack.rotate_z(theta);
}

void GraphicsLib::push_matrix()
{
   matrix_stack.push_matrix();
}

void GraphicsLib::pop_matrix()
{
   matrix_stack.pop_matrix();
}

TransformMatrix& GraphicsLib::get_ctm()
{
   return matrix_stack.get_ctm();
}

int32_t GraphicsLib::size()
{
   return matrix_stack.size();
}

