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
   gl->add_vertex (1, 1, 0);
   gl->add_vertex (2, 2, 0);
   gl->end_shape();
    
   EXPECT_EQ(0, 0);
    
}
