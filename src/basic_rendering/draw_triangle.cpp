#include <graphics_lib.h>

int main()
{
	Vector2 A(250.0f, 250.0f);
	Color A_color(1.0, 0.0, 0.0);
	Vector2 B(150.0f, 750.0f);
	Color B_color(0.0, 1.0, 0.0);
	Vector2 C(350.0f, 750.0f);
	Color C_color(0.0, 0.0, 1.0);

    GraphicsLib gl = GraphicsLib();
    gl.create_window("Hello, there!", 1000, 1000);
    while(gl.window.open())
    {
		gl.draw_triangle(A, A_color, B, B_color, C, C_color);
        gl.window.update();
    }
}
