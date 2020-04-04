#include <graphics_lib.h>

void main()
{
    Window test_window = GraphicsLib::create_window("Hello, there!", 1000, 1000);
    while(test_window.open())
    {
        GraphicsLig::drawTriangle();
        test_window.update();
    }
}
