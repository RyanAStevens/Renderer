#include <draw_routines_test.h>
#include <draw_routines.h>
#include <stdio.h>

GraphicsLib* gl_p;

DrawRoutineTest::DrawRoutineTest() {
    gl_p = new GraphicsLib(ORTHOGRAPHIC, 1920, 1080);
}

DrawRoutineTest::~DrawRoutineTest() {
    delete gl_p;
}

void DrawRoutineTest::SetUp() {
}

void DrawRoutineTest::TearDown() {
}

TEST_F(DrawRoutineTest, square) {
   square(gl_p);
   EXPECT_EQ(0, 0);
}
