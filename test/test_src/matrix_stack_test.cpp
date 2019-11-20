#include <matrix_stack_test.h>
#include <matrix_stack.h>

MatrixStackTest::MatrixStackTest() {
    MatrixStack matStack = MatrixStack();
//    std::cout << "hello from MatrixStackTest constructor.\n";
}

MatrixStackTest::~MatrixStackTest() {
//    std::cout << "hello from MatrixStackTest destructor.\n";
}

void MatrixStackTest::SetUp() {
//    std::cout << "hello from google test SetUp().\n";
}

void MatrixStackTest::TearDown() {
//    std::cout << "hello from google test TearDown().\n";
}

TEST_F(MatrixStackTest, InitOnly) {
    matStack.initialize()
    matStack.print_ctm()
}
    
TEST_F(MatrixStackTest, Traslate) {
    matStack.initialize()
    matStack.translate(3,2,1.5)
    matStack.print_ctm()
}

TEST_F(MatrixStackTest, Scale) {
    matStack.initialize()
    matStack.scale(2,3,4)
    matStack.print_ctm()
}

TEST_F(MatrixStackTest, RotateX) {
    matStack.initialize()
    matStack.rotateX(90)
    matStack.print_ctm()
}

TEST_F(MatrixStackTest, RotateY) {
    matStack.initialize()
    matStack.rotateY(-15)
    matStack.print_ctm()
}

TEST_F(MatrixStackTest, RotateZ) {
    matStack.initialize()
    matStack.pushMatrix()
    matStack.rotateZ(45)
    matStack.print_ctm()
    matStack.popMatrix()
    matStack.print_ctm()
}

TEST_F(MatrixStackTest, TranslateScale) {
    matStack.initialize()
    matStack.translate(1.5,2.5,3.5)
    matStack.scale(2,2,2)
    matStack.print_ctm()
}

TEST_F(MatrixStackTest, ScaleTranslate) {
    matStack.initialize()
    matStack.scale(2,2,2)
    matStack.translate(1.5,2.5,3.5)
    matStack.print_ctm()
}

TEST_F(MatrixStackTest, ScalePushTranslatePop) {
    matStack.initialize()
    matStack.scale(2,2,2)
    matStack.pushMatrix()
    matStack.translate(1.5,2.5,3.5)
    matStack.print_ctm()
    matStack.popMatrix()
    matStack.print_ctm()
}

TEST_F(MatrixStackTest, InitPop) {
    matStack.initialize()
    matStack.popMatrix()
}
