#include <graphics_lib_test.h>
#include <graphics_lib.h>
#include <stdio.h>

GraphicsLib* gl;

GraphicsLibTest::GraphicsLibTest() {
    gl = new GraphicsLib(ORTHOGRAPHIC, 1920, 1080);
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
    gl->set_view(Vector3(0,0,0), Vector3(1,0,-1), Vector3(0,1,0)); 
    printf("m_view:\n");
    gl->m_view->print();
    printf("\n");
    //apply current transformation
    Vertex vert1 = Vertex(1.0, 0,0); 
    printf("vertex transform: before\n");
    vert1.print();
    //vert1 = *(projection->matrix) * *m_view * ctm * vert1;
    vert1 = *gl->m_view * vert1;
    printf("\nvertex transform: after\n");
    vert1.print();
    
    EXPECT_EQ(0, 0);
}
