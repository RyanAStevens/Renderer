#include <graphics_lib.h>
#include <stdio.h>

int main()
{
    printf("hello from draw_triangle\n");
	Vector2 A(250.0f, 250.0f);
    printf("1\n");
	Color A_color(1.0, 0.0, 0.0);
    printf("2\n");
	Vector2 B(150.0f, 750.0f);
    printf("3\n");
	Color B_color(0.0, 1.0, 0.0);
    printf("4\n");
	Vector2 C(350.0f, 750.0f);
    printf("5\n");
	Color C_color(0.0, 0.0, 1.0);
    printf("6\n");

    GraphicsLib gl = GraphicsLib();
    printf("7\n");
    Window window = Window("Hello, there!", 1000, 1000);
    printf("8\n");
    while(window.open())
    {
		gl.draw_triangle(A, A_color, B, B_color, C, C_color);
        printf("draw the triangle\n");
        window.update();
    }
}
