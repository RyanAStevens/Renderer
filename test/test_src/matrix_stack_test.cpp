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

    TransformMatrix ctm = matStack->get_ctm();
    EXPECT_EQ(ctm.row[0].components[0], 1);
    EXPECT_EQ(ctm.row[0].components[1], 0);
    EXPECT_EQ(ctm.row[0].components[2], 0);
    EXPECT_EQ(ctm.row[0].components[3], 0);

    EXPECT_EQ(ctm.row[1].components[0], 0);
    EXPECT_EQ(ctm.row[1].components[1], 1);
    EXPECT_EQ(ctm.row[1].components[2], 0);
    EXPECT_EQ(ctm.row[1].components[3], 0);
    
    EXPECT_EQ(ctm.row[2].components[0], 0);
    EXPECT_EQ(ctm.row[2].components[1], 0);
    EXPECT_EQ(ctm.row[2].components[2], 1);
    EXPECT_EQ(ctm.row[2].components[3], 0);
    
    EXPECT_EQ(ctm.row[3].components[0], 0);
    EXPECT_EQ(ctm.row[3].components[1], 0);
    EXPECT_EQ(ctm.row[3].components[2], 0);
    EXPECT_EQ(ctm.row[3].components[3], 1);
}
    
TEST_F(MatrixStackTest, Traslate) {
    matStack->initialize();
    matStack->translate(3,2,1.5);

    TransformMatrix ctm = matStack->get_ctm();
    EXPECT_EQ(ctm.row[0].components[0], 1);
    EXPECT_EQ(ctm.row[0].components[1], 0);
    EXPECT_EQ(ctm.row[0].components[2], 0);
    EXPECT_EQ(ctm.row[0].components[3], 3.0);

    EXPECT_EQ(ctm.row[1].components[0], 0);
    EXPECT_EQ(ctm.row[1].components[1], 1);
    EXPECT_EQ(ctm.row[1].components[2], 0);
    EXPECT_EQ(ctm.row[1].components[3], 2.0);
    
    EXPECT_EQ(ctm.row[2].components[0], 0);
    EXPECT_EQ(ctm.row[2].components[1], 0);
    EXPECT_EQ(ctm.row[2].components[2], 1);
    EXPECT_EQ(ctm.row[2].components[3], 1.5);
    
    EXPECT_EQ(ctm.row[3].components[0], 0);
    EXPECT_EQ(ctm.row[3].components[1], 0);
    EXPECT_EQ(ctm.row[3].components[2], 0);
    EXPECT_EQ(ctm.row[3].components[3], 1.0);
}

TEST_F(MatrixStackTest, Scale) {
    matStack->initialize();
    matStack->scale(2,3,4);

    TransformMatrix ctm = matStack->get_ctm();
    EXPECT_EQ(ctm.row[0].components[0], 2);
    EXPECT_EQ(ctm.row[0].components[1], 0);
    EXPECT_EQ(ctm.row[0].components[2], 0);
    EXPECT_EQ(ctm.row[0].components[3], 0);

    EXPECT_EQ(ctm.row[1].components[0], 0);
    EXPECT_EQ(ctm.row[1].components[1], 3);
    EXPECT_EQ(ctm.row[1].components[2], 0);
    EXPECT_EQ(ctm.row[1].components[3], 0);
    
    EXPECT_EQ(ctm.row[2].components[0], 0);
    EXPECT_EQ(ctm.row[2].components[1], 0);
    EXPECT_EQ(ctm.row[2].components[2], 4);
    EXPECT_EQ(ctm.row[2].components[3], 0);
    
    EXPECT_EQ(ctm.row[3].components[0], 0);
    EXPECT_EQ(ctm.row[3].components[1], 0);
    EXPECT_EQ(ctm.row[3].components[2], 0);
    EXPECT_EQ(ctm.row[3].components[3], 1);
}

TEST_F(MatrixStackTest, RotateX) {
    matStack->initialize();
    matStack->rotateX(90);

    TransformMatrix ctm = matStack->get_ctm();
    EXPECT_EQ(ctm.row[0].components[0], 1);
    EXPECT_EQ(ctm.row[0].components[1], 0.0);
    EXPECT_EQ(ctm.row[0].components[2], 0.0);
    EXPECT_EQ(ctm.row[0].components[3], 0);

    EXPECT_EQ(ctm.row[1].components[0], 0);
    EXPECT_EQ(ctm.row[1].components[1], -4.371138828673792886547744274139404296875e-08);
    EXPECT_EQ(ctm.row[1].components[2], -1.0);
    EXPECT_EQ(ctm.row[1].components[3], 0);
    
    EXPECT_EQ(ctm.row[2].components[0], 0);
    EXPECT_EQ(ctm.row[2].components[1], 1.0);
    EXPECT_EQ(ctm.row[2].components[2], -4.371138828673792886547744274139404296875e-08);
    EXPECT_EQ(ctm.row[2].components[3], 0);
    
    EXPECT_EQ(ctm.row[3].components[0], 0);
    EXPECT_EQ(ctm.row[3].components[1], 0);
    EXPECT_EQ(ctm.row[3].components[2], 0);
    EXPECT_EQ(ctm.row[3].components[3], 1);
}

TEST_F(MatrixStackTest, RotateY) {
    matStack->initialize();
    matStack->rotateY(-15);

    TransformMatrix ctm = matStack->get_ctm();
    EXPECT_EQ(ctm.row[0].components[0], 0.9659258127212524);
    EXPECT_EQ(ctm.row[0].components[1], 0);
    EXPECT_EQ(ctm.row[0].components[2], -0.258819043636322021484375);
    EXPECT_EQ(ctm.row[0].components[3], 0);

    EXPECT_EQ(ctm.row[1].components[0], 0.0);
    EXPECT_EQ(ctm.row[1].components[1], 1);
    EXPECT_EQ(ctm.row[1].components[2], 0.0);
    EXPECT_EQ(ctm.row[1].components[3], 0);
    
    EXPECT_EQ(ctm.row[2].components[0], 0.258819043636322021484375);
    EXPECT_EQ(ctm.row[2].components[1], 0);
    EXPECT_EQ(ctm.row[2].components[2], 0.9659258127212524);
    EXPECT_EQ(ctm.row[2].components[3], 0);
    
    EXPECT_EQ(ctm.row[3].components[0], 0.0);
    EXPECT_EQ(ctm.row[3].components[1], 0.0);
    EXPECT_EQ(ctm.row[3].components[2], 0);
    EXPECT_EQ(ctm.row[3].components[3], 1);
}

TEST_F(MatrixStackTest, RotateZ) {
    matStack->initialize();
    matStack->rotateZ(45);

    TransformMatrix ctm = matStack->get_ctm();
    EXPECT_EQ(ctm.row[0].components[0],0.7071067690849304199218750);
    EXPECT_EQ(ctm.row[0].components[1],-0.7071067690849304199218750);
    EXPECT_EQ(ctm.row[0].components[2], 0);
    EXPECT_EQ(ctm.row[0].components[3], 0);

    EXPECT_EQ(ctm.row[1].components[0], 0.7071067690849304199218750);
    EXPECT_EQ(ctm.row[1].components[1], 0.7071067690849304199218750);
    EXPECT_EQ(ctm.row[1].components[2], 0);
    EXPECT_EQ(ctm.row[1].components[3], 0);
    
    EXPECT_EQ(ctm.row[2].components[0], 0);
    EXPECT_EQ(ctm.row[2].components[1], 0);
    EXPECT_EQ(ctm.row[2].components[2], 1);
    EXPECT_EQ(ctm.row[2].components[3], 0);
    
    EXPECT_EQ(ctm.row[3].components[0], 0);
    EXPECT_EQ(ctm.row[3].components[1], 0);
    EXPECT_EQ(ctm.row[3].components[2], 0);
    EXPECT_EQ(ctm.row[3].components[3], 1);
}

TEST_F(MatrixStackTest, TranslateScale) {
    matStack->initialize();
    matStack->translate(1.5,2.5,3.5);
    matStack->scale(2,2,2);

    TransformMatrix ctm = matStack->get_ctm();
    EXPECT_EQ(ctm.row[0].components[0], 2.0);
    EXPECT_EQ(ctm.row[0].components[1], 0);
    EXPECT_EQ(ctm.row[0].components[2], 0);
    EXPECT_EQ(ctm.row[0].components[3], 1.5);

    EXPECT_EQ(ctm.row[1].components[0], 0);
    EXPECT_EQ(ctm.row[1].components[1], 2.0);
    EXPECT_EQ(ctm.row[1].components[2], 0);
    EXPECT_EQ(ctm.row[1].components[3], 2.5);
    
    EXPECT_EQ(ctm.row[2].components[0], 0);
    EXPECT_EQ(ctm.row[2].components[1], 0);
    EXPECT_EQ(ctm.row[2].components[2], 2.0);
    EXPECT_EQ(ctm.row[2].components[3], 3.5);
    
    EXPECT_EQ(ctm.row[3].components[0], 0);
    EXPECT_EQ(ctm.row[3].components[1], 0);
    EXPECT_EQ(ctm.row[3].components[2], 0);
    EXPECT_EQ(ctm.row[3].components[3], 1.0);
}

TEST_F(MatrixStackTest, ScaleTranslate) {
    matStack->initialize();
    matStack->scale(2,2,2);
    matStack->translate(1.5,2.5,3.5);

    TransformMatrix ctm = matStack->get_ctm();
    EXPECT_EQ(ctm.row[0].components[0], 2);
    EXPECT_EQ(ctm.row[0].components[1], 0);
    EXPECT_EQ(ctm.row[0].components[2], 0);
    EXPECT_EQ(ctm.row[0].components[3], 3.0);

    EXPECT_EQ(ctm.row[1].components[0], 0);
    EXPECT_EQ(ctm.row[1].components[1], 2);
    EXPECT_EQ(ctm.row[1].components[2], 0);
    EXPECT_EQ(ctm.row[1].components[3], 5.0);
    
    EXPECT_EQ(ctm.row[2].components[0], 0);
    EXPECT_EQ(ctm.row[2].components[1], 0);
    EXPECT_EQ(ctm.row[2].components[2], 2);
    EXPECT_EQ(ctm.row[2].components[3], 7.0);
    
    EXPECT_EQ(ctm.row[3].components[0], 0);
    EXPECT_EQ(ctm.row[3].components[1], 0);
    EXPECT_EQ(ctm.row[3].components[2], 0);
    EXPECT_EQ(ctm.row[3].components[3], 1.0);
}

TEST_F(MatrixStackTest, ScalePushTranslatePop) {
    matStack->initialize();
    matStack->scale(2,2,2);
    matStack->pushMatrix();
    matStack->translate(1.5,2.5,3.5);

    TransformMatrix ctm = matStack->get_ctm();
    EXPECT_EQ(ctm.row[0].components[0], 2);
    EXPECT_EQ(ctm.row[0].components[1], 0);
    EXPECT_EQ(ctm.row[0].components[2], 0);
    EXPECT_EQ(ctm.row[0].components[3], 3.0);

    EXPECT_EQ(ctm.row[1].components[0], 0);
    EXPECT_EQ(ctm.row[1].components[1], 2);
    EXPECT_EQ(ctm.row[1].components[2], 0);
    EXPECT_EQ(ctm.row[1].components[3], 5.0);
    
    EXPECT_EQ(ctm.row[2].components[0], 0);
    EXPECT_EQ(ctm.row[2].components[1], 0);
    EXPECT_EQ(ctm.row[2].components[2], 2);
    EXPECT_EQ(ctm.row[2].components[3], 7.0);
    
    EXPECT_EQ(ctm.row[3].components[0], 0);
    EXPECT_EQ(ctm.row[3].components[1], 0);
    EXPECT_EQ(ctm.row[3].components[2], 0);
    EXPECT_EQ(ctm.row[3].components[3], 1.0);
    
    matStack->popMatrix();
    ctm = matStack->get_ctm();
    EXPECT_EQ(ctm.row[0].components[0], 2);
    EXPECT_EQ(ctm.row[0].components[1], 0);
    EXPECT_EQ(ctm.row[0].components[2], 0);
    EXPECT_EQ(ctm.row[0].components[3], 0);

    EXPECT_EQ(ctm.row[1].components[0], 0);
    EXPECT_EQ(ctm.row[1].components[1], 2);
    EXPECT_EQ(ctm.row[1].components[2], 0);
    EXPECT_EQ(ctm.row[1].components[3], 0);
    
    EXPECT_EQ(ctm.row[2].components[0], 0);
    EXPECT_EQ(ctm.row[2].components[1], 0);
    EXPECT_EQ(ctm.row[2].components[2], 2);
    EXPECT_EQ(ctm.row[2].components[3], 0);
    
    EXPECT_EQ(ctm.row[3].components[0], 0);
    EXPECT_EQ(ctm.row[3].components[1], 0);
    EXPECT_EQ(ctm.row[3].components[2], 0);
    EXPECT_EQ(ctm.row[3].components[3], 1);
}

TEST_F(MatrixStackTest, InitPop) {
    matStack->initialize();
    EXPECT_EQ(matStack->popMatrix(), 0);
}

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

    std::cout << "matStack->initialize();\nmatStack->rotateX(90);\n";
    matStack->initialize();
    matStack->rotateX(90);
    matStack->print_ctm();

    std::cout << "matStack->initialize();\nmatStack->rotateY(-15);\n";
    matStack->initialize();
    matStack->rotateY(-15);
    matStack->print_ctm();

    std::cout << "matStack->initialize();\nmatStack->pushMatrix();\nmatStack->rotateZ(45);\n;";
    matStack->initialize();
    matStack->pushMatrix();
    matStack->rotateZ(45);
    matStack->print_ctm();
    
    std::cout << "matStack->popMatrix();\n";
    matStack->popMatrix();
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

    std::cout << "matStack->initialize();\nmatStack->scale(2,2,2);\nmatStack->pushMatrix();\nmatStack->translate(1.5,2.5,3.5);\nmatStack->popMatrix();\n";
    matStack->initialize();
    matStack->scale(2,2,2);
    matStack->pushMatrix();
    matStack->translate(1.5,2.5,3.5);
    matStack->popMatrix();
    matStack->print_ctm();

    std::cout << "matStack->initialize();\nmatStack->popMatrix();\nmatStack->popMatrix();\n";
    matStack->initialize();
    matStack->popMatrix();
    matStack->popMatrix();
}
