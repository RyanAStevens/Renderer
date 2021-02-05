#include <matrix_stack_test.h>
#include <matrix_stack.h>
#include <math.h>
#include <stdio.h>

MatrixStack* matStack;

MatrixStackTest::MatrixStackTest() {
    matStack = new MatrixStack();
//    std::cout << "hello from MatrixStackTest constructor.\n";
}

MatrixStackTest::~MatrixStackTest() {
//    std::cout << "hello from MatrixStackTest destructor.\n";
    delete matStack;
}

void MatrixStackTest::SetUp() {
//    std::cout << "hello from google test SetUp().\n";
}

void MatrixStackTest::TearDown() {
//    std::cout << "hello from google test TearDown().\n";
}

TEST_F(MatrixStackTest, InitOnly) {
    matStack->initialize();

    Matrix ctm = matStack->get_ctm();
    EXPECT_EQ((*ctm.data)[0][0], 1);
    EXPECT_EQ((*ctm.data)[0][1], 0);
    EXPECT_EQ((*ctm.data)[0][2], 0);
    EXPECT_EQ((*ctm.data)[0][3], 0);

    EXPECT_EQ((*ctm.data)[1][0], 0);
    EXPECT_EQ((*ctm.data)[1][1], 1);
    EXPECT_EQ((*ctm.data)[1][2], 0);
    EXPECT_EQ((*ctm.data)[1][3], 0);
    
    EXPECT_EQ((*ctm.data)[2][0], 0);
    EXPECT_EQ((*ctm.data)[2][1], 0);
    EXPECT_EQ((*ctm.data)[2][2], 1);
    EXPECT_EQ((*ctm.data)[2][3], 0);
    
    EXPECT_EQ((*ctm.data)[3][0], 0);
    EXPECT_EQ((*ctm.data)[3][1], 0);
    EXPECT_EQ((*ctm.data)[3][2], 0);
    EXPECT_EQ((*ctm.data)[3][3], 1);
}
    
TEST_F(MatrixStackTest, Traslate) {
    matStack->initialize();
    matStack->translate(3,2,1.5);

    Matrix ctm = matStack->get_ctm();
    EXPECT_EQ((*ctm.data)[0][0], 1);
    EXPECT_EQ((*ctm.data)[0][1], 0);
    EXPECT_EQ((*ctm.data)[0][2], 0);
    EXPECT_EQ((*ctm.data)[0][3], 3.0);

    EXPECT_EQ((*ctm.data)[1][0], 0);
    EXPECT_EQ((*ctm.data)[1][1], 1);
    EXPECT_EQ((*ctm.data)[1][2], 0);
    EXPECT_EQ((*ctm.data)[1][3], 2.0);
    
    EXPECT_EQ((*ctm.data)[2][0], 0);
    EXPECT_EQ((*ctm.data)[2][1], 0);
    EXPECT_EQ((*ctm.data)[2][2], 1);
    EXPECT_EQ((*ctm.data)[2][3], 1.5);
    
    EXPECT_EQ((*ctm.data)[3][0], 0);
    EXPECT_EQ((*ctm.data)[3][1], 0);
    EXPECT_EQ((*ctm.data)[3][2], 0);
    EXPECT_EQ((*ctm.data)[3][3], 1.0);
}

TEST_F(MatrixStackTest, Scale) {
    matStack->initialize();
    matStack->scale(2,3,4);

    Matrix ctm = matStack->get_ctm();
    EXPECT_EQ((*ctm.data)[0][0], 2);
    EXPECT_EQ((*ctm.data)[0][1], 0);
    EXPECT_EQ((*ctm.data)[0][2], 0);
    EXPECT_EQ((*ctm.data)[0][3], 0);

    EXPECT_EQ((*ctm.data)[1][0], 0);
    EXPECT_EQ((*ctm.data)[1][1], 3);
    EXPECT_EQ((*ctm.data)[1][2], 0);
    EXPECT_EQ((*ctm.data)[1][3], 0);
    
    EXPECT_EQ((*ctm.data)[2][0], 0);
    EXPECT_EQ((*ctm.data)[2][1], 0);
    EXPECT_EQ((*ctm.data)[2][2], 4);
    EXPECT_EQ((*ctm.data)[2][3], 0);
    
    EXPECT_EQ((*ctm.data)[3][0], 0);
    EXPECT_EQ((*ctm.data)[3][1], 0);
    EXPECT_EQ((*ctm.data)[3][2], 0);
    EXPECT_EQ((*ctm.data)[3][3], 1);
}

TEST_F(MatrixStackTest, RotateX) {
    matStack->initialize();
    matStack->rotate_x(90);

    Matrix ctm = matStack->get_ctm();
    EXPECT_EQ((*ctm.data)[0][0], 1);
    EXPECT_EQ((*ctm.data)[0][1], 0.0);
    EXPECT_EQ((*ctm.data)[0][2], 0.0);
    EXPECT_EQ((*ctm.data)[0][3], 0);

    EXPECT_EQ((*ctm.data)[1][0], 0);
    EXPECT_EQ((*ctm.data)[1][1], -4.371138828673792886547744274139404296875e-08);
    EXPECT_EQ((*ctm.data)[1][2], -1.0);
    EXPECT_EQ((*ctm.data)[1][3], 0);
    
    EXPECT_EQ((*ctm.data)[2][0], 0);
    EXPECT_EQ((*ctm.data)[2][1], 1.0);
    EXPECT_EQ((*ctm.data)[2][2], -4.371138828673792886547744274139404296875e-08);
    EXPECT_EQ((*ctm.data)[2][3], 0);
    
    EXPECT_EQ((*ctm.data)[3][0], 0);
    EXPECT_EQ((*ctm.data)[3][1], 0);
    EXPECT_EQ((*ctm.data)[3][2], 0);
    EXPECT_EQ((*ctm.data)[3][3], 1);
}

TEST_F(MatrixStackTest, RotateY) {
    matStack->initialize();
    matStack->rotate_y(-15);

    Matrix ctm = matStack->get_ctm();
    EXPECT_EQ((*ctm.data)[0][0], 0.9659258127212524);
    EXPECT_EQ((*ctm.data)[0][1], 0);
    EXPECT_EQ((*ctm.data)[0][2], -0.258819043636322021484375);
    EXPECT_EQ((*ctm.data)[0][3], 0);

    EXPECT_EQ((*ctm.data)[1][0], 0.0);
    EXPECT_EQ((*ctm.data)[1][1], 1);
    EXPECT_EQ((*ctm.data)[1][2], 0.0);
    EXPECT_EQ((*ctm.data)[1][3], 0);
    
    EXPECT_EQ((*ctm.data)[2][0], 0.258819043636322021484375);
    EXPECT_EQ((*ctm.data)[2][1], 0);
    EXPECT_EQ((*ctm.data)[2][2], 0.9659258127212524);
    EXPECT_EQ((*ctm.data)[2][3], 0);
    
    EXPECT_EQ((*ctm.data)[3][0], 0.0);
    EXPECT_EQ((*ctm.data)[3][1], 0.0);
    EXPECT_EQ((*ctm.data)[3][2], 0);
    EXPECT_EQ((*ctm.data)[3][3], 1);
}

TEST_F(MatrixStackTest, RotateZ) {
    matStack->initialize();
    matStack->rotate_z(45);

    Matrix ctm = matStack->get_ctm();
    EXPECT_EQ((*ctm.data)[0][0],0.7071067690849304199218750);
    EXPECT_EQ((*ctm.data)[0][1],-0.7071067690849304199218750);
    EXPECT_EQ((*ctm.data)[0][2], 0);
    EXPECT_EQ((*ctm.data)[0][3], 0);

    EXPECT_EQ((*ctm.data)[1][0], 0.7071067690849304199218750);
    EXPECT_EQ((*ctm.data)[1][1], 0.7071067690849304199218750);
    EXPECT_EQ((*ctm.data)[1][2], 0);
    EXPECT_EQ((*ctm.data)[1][3], 0);
    
    EXPECT_EQ((*ctm.data)[2][0], 0);
    EXPECT_EQ((*ctm.data)[2][1], 0);
    EXPECT_EQ((*ctm.data)[2][2], 1);
    EXPECT_EQ((*ctm.data)[2][3], 0);
    
    EXPECT_EQ((*ctm.data)[3][0], 0);
    EXPECT_EQ((*ctm.data)[3][1], 0);
    EXPECT_EQ((*ctm.data)[3][2], 0);
    EXPECT_EQ((*ctm.data)[3][3], 1);
}

TEST_F(MatrixStackTest, TranslateScale) {
    matStack->initialize();
    matStack->translate(1.5,2.5,3.5);
    matStack->scale(2,2,2);

    Matrix ctm = matStack->get_ctm();
    EXPECT_EQ((*ctm.data)[0][0], 2.0);
    EXPECT_EQ((*ctm.data)[0][1], 0);
    EXPECT_EQ((*ctm.data)[0][2], 0);
    EXPECT_EQ((*ctm.data)[0][3], 1.5);

    EXPECT_EQ((*ctm.data)[1][0], 0);
    EXPECT_EQ((*ctm.data)[1][1], 2.0);
    EXPECT_EQ((*ctm.data)[1][2], 0);
    EXPECT_EQ((*ctm.data)[1][3], 2.5);
    
    EXPECT_EQ((*ctm.data)[2][0], 0);
    EXPECT_EQ((*ctm.data)[2][1], 0);
    EXPECT_EQ((*ctm.data)[2][2], 2.0);
    EXPECT_EQ((*ctm.data)[2][3], 3.5);
    
    EXPECT_EQ((*ctm.data)[3][0], 0);
    EXPECT_EQ((*ctm.data)[3][1], 0);
    EXPECT_EQ((*ctm.data)[3][2], 0);
    EXPECT_EQ((*ctm.data)[3][3], 1.0);
}

TEST_F(MatrixStackTest, ScaleTranslate) {
    matStack->initialize();
    matStack->scale(2,2,2);
    matStack->translate(1.5,2.5,3.5);

    Matrix ctm = matStack->get_ctm();
    EXPECT_EQ((*ctm.data)[0][0], 2);
    EXPECT_EQ((*ctm.data)[0][1], 0);
    EXPECT_EQ((*ctm.data)[0][2], 0);
    EXPECT_EQ((*ctm.data)[0][3], 3.0);

    EXPECT_EQ((*ctm.data)[1][0], 0);
    EXPECT_EQ((*ctm.data)[1][1], 2);
    EXPECT_EQ((*ctm.data)[1][2], 0);
    EXPECT_EQ((*ctm.data)[1][3], 5.0);
    
    EXPECT_EQ((*ctm.data)[2][0], 0);
    EXPECT_EQ((*ctm.data)[2][1], 0);
    EXPECT_EQ((*ctm.data)[2][2], 2);
    EXPECT_EQ((*ctm.data)[2][3], 7.0);
    
    EXPECT_EQ((*ctm.data)[3][0], 0);
    EXPECT_EQ((*ctm.data)[3][1], 0);
    EXPECT_EQ((*ctm.data)[3][2], 0);
    EXPECT_EQ((*ctm.data)[3][3], 1.0);
}

TEST_F(MatrixStackTest, ScalePushTranslatePop) {
    matStack->initialize();
    matStack->scale(2,2,2);
    matStack->push_matrix();
    matStack->translate(1.5,2.5,3.5);

    Matrix ctm = matStack->get_ctm();
    EXPECT_EQ((*ctm.data)[0][0], 2);
    EXPECT_EQ((*ctm.data)[0][1], 0);
    EXPECT_EQ((*ctm.data)[0][2], 0);
    EXPECT_EQ((*ctm.data)[0][3], 3.0);

    EXPECT_EQ((*ctm.data)[1][0], 0);
    EXPECT_EQ((*ctm.data)[1][1], 2);
    EXPECT_EQ((*ctm.data)[1][2], 0);
    EXPECT_EQ((*ctm.data)[1][3], 5.0);
    
    EXPECT_EQ((*ctm.data)[2][0], 0);
    EXPECT_EQ((*ctm.data)[2][1], 0);
    EXPECT_EQ((*ctm.data)[2][2], 2);
    EXPECT_EQ((*ctm.data)[2][3], 7.0);
    
    EXPECT_EQ((*ctm.data)[3][0], 0);
    EXPECT_EQ((*ctm.data)[3][1], 0);
    EXPECT_EQ((*ctm.data)[3][2], 0);
    EXPECT_EQ((*ctm.data)[3][3], 1.0);
    
    matStack->pop_matrix();
    ctm = matStack->get_ctm();
    EXPECT_EQ((*ctm.data)[0][0], 2);
    EXPECT_EQ((*ctm.data)[0][1], 0);
    EXPECT_EQ((*ctm.data)[0][2], 0);
    EXPECT_EQ((*ctm.data)[0][3], 0);

    EXPECT_EQ((*ctm.data)[1][0], 0);
    EXPECT_EQ((*ctm.data)[1][1], 2);
    EXPECT_EQ((*ctm.data)[1][2], 0);
    EXPECT_EQ((*ctm.data)[1][3], 0);
    
    EXPECT_EQ((*ctm.data)[2][0], 0);
    EXPECT_EQ((*ctm.data)[2][1], 0);
    EXPECT_EQ((*ctm.data)[2][2], 2);
    EXPECT_EQ((*ctm.data)[2][3], 0);
    
    EXPECT_EQ((*ctm.data)[3][0], 0);
    EXPECT_EQ((*ctm.data)[3][1], 0);
    EXPECT_EQ((*ctm.data)[3][2], 0);
    EXPECT_EQ((*ctm.data)[3][3], 1);
}

TEST_F(MatrixStackTest, InitPop) {
    matStack->initialize();
    EXPECT_EQ(matStack->pop_matrix(), 0);
}

/*
TEST_F(MatrixStackTest, PrintAll) {
    std::cout << "matStack->initialize();\n";
    matStack->initialize();
    matStack->print_ctm();
    
    std::cout << "matStack->initialize();\nmatStack->translate(3,2,1.5);\n";
    matStack->initialize();
    matStack->translate(3,2,1.5);
    matStack->print_ctm();

    std::cout << "matStack->initialize();\nmatStack->scale(2,3,4);\n";
    matStack->initialize();
    matStack->scale(2,3,4);
    matStack->print_ctm();

    std::cout << "matStack->initialize();\nmatStack->rotate_x(90);\n";
    matStack->initialize();
    matStack->rotate_x(90);
    matStack->print_ctm();

    std::cout << "matStack->initialize();\nmatStack->rotate_y(-15);\n";
    matStack->initialize();
    matStack->rotate_y(-15);
    matStack->print_ctm();

    std::cout << "matStack->initialize();\nmatStack->push_matrix();\nmatStack->rotate_z(45);\n;";
    matStack->initialize();
    matStack->push_matrix();
    matStack->rotate_z(45);
    matStack->print_ctm();
    
    std::cout << "matStack->pop_matrix();\n";
    matStack->pop_matrix();
    matStack->print_ctm();

    std::cout << "matStack->initialize();\n";
    matStack->initialize();
    matStack->print_ctm();
    std::cout << "matStack->translate(1.5,2.5,3.5);\n";
    matStack->translate(1.5,2.5,3.5);
    matStack->print_ctm();
    std::cout << "matStack->scale(2,2,2);\n";
    matStack->scale(2,2,2);
    matStack->print_ctm();

    std::cout << "matStack->initialize();\n";
    matStack->initialize();
    matStack->print_ctm();
    std::cout << "matStack->scale(2,2,2);\n";
    matStack->scale(2,2,2);
    matStack->print_ctm();
    std::cout << "matStack->translate(1.5,2.5,3.5);\n";
    matStack->translate(1.5,2.5,3.5);
    matStack->print_ctm();

    std::cout << "matStack->initialize();\nmatStack->scale(2,2,2);\nmatStack->push_matrix();\nmatStack->translate(1.5,2.5,3.5);\nmatStack->pop_matrix();\n";
    matStack->initialize();
    matStack->scale(2,2,2);
    matStack->push_matrix();
    matStack->translate(1.5,2.5,3.5);
    matStack->pop_matrix();
    matStack->print_ctm();

    std::cout << "matStack->initialize();\nmatStack->pop_matrix();\nmatStack->pop_matrix();\n";
    matStack->initialize();
    matStack->pop_matrix();
    matStack->pop_matrix();
}
*/
