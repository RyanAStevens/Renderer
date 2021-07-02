#include <graphics_lib_test.h>
#include <graphics_lib.h>
#include <stdio.h>

GraphicsLib* gl;

GraphicsLibTest::GraphicsLibTest() {
    gl = new GraphicsLib(PERSPECTIVE, 1920, 1080);
//    std::cout << "hello from GraphicsLibTest constructor.\n";
}

GraphicsLibTest::~GraphicsLibTest() {
//    std::cout << "hello from GraphicsLibTest destructor.\n";
    delete gl;
}

void GraphicsLibTest::SetUp() {
//    std::cout << "hello from google test SetUp().\n";
}

void GraphicsLibTest::TearDown() {
//    std::cout << "hello from google test TearDown().\n";
}

TEST_F(GraphicsLibTest, begin_end_shape_line) {
   gl->begin_shape();
   gl->add_vertex (0.25, 0.25, 0);
   gl->add_vertex (0.5, 0.5, 0);
   gl->end_shape();
    
   EXPECT_EQ(0, 0);
}

TEST_F(GraphicsLibTest, set_view) {
    Vertex ortho_vert = Vertex(1.0, 0,0);
    gl->projection->set_projection(ORTHOGRAPHIC);
    gl->set_view(Vector3(0,0,0), Vector3(1,0,-1), Vector3(0,1,0)); 
    ortho_vert = *gl->projection->matrix * *gl->m_view * *gl->m_window * ortho_vert;
    EXPECT_EQ(ortho_vert == Vertex(135.693787, 53.899998, -135.693787), true);

    Vertex persp_vert = Vertex(1.0, 0,0);
    gl->projection->set_projection(PERSPECTIVE);
    persp_vert = *gl->projection->matrix * *gl->m_view * *gl->m_window * persp_vert;
    EXPECT_EQ(persp_vert == Vertex(1356.937988, 538.999939, 100.000000), true);
}
