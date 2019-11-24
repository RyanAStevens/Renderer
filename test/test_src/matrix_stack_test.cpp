#include <matrix_stack_test.h>
#include <matrix_stack.h>

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
    EXPECT_EQ(ctm.row[1].components[1], -0.000000043711388);
    EXPECT_EQ(ctm.row[1].components[2], -1.0);
    EXPECT_EQ(ctm.row[1].components[3], 0);
    
    EXPECT_EQ(ctm.row[2].components[0], 0);
    EXPECT_EQ(ctm.row[2].components[1], 1.0);
    EXPECT_EQ(ctm.row[2].components[2], -0.000000043711388);
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
    EXPECT_EQ(ctm.row[0].components[2], -0.2588190436636322);
    EXPECT_EQ(ctm.row[0].components[3], 0);

    EXPECT_EQ(ctm.row[1].components[0], 0.0);
    EXPECT_EQ(ctm.row[1].components[1], 1);
    EXPECT_EQ(ctm.row[1].components[2], 0.0);
    EXPECT_EQ(ctm.row[1].components[3], 0);
    
    EXPECT_EQ(ctm.row[2].components[0], 0.2588190436636322);
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
    matStack->pushMatrix();
    matStack->rotateZ(45);
    matStack->print_ctm();
    matStack->popMatrix();

    TransformMatrix ctm = matStack->get_ctm();
    EXPECT_EQ(ctm.row[0].components[0], 0);
    EXPECT_EQ(ctm.row[0].components[1], 0);
    EXPECT_EQ(ctm.row[0].components[2], 0);
    EXPECT_EQ(ctm.row[0].components[3], 0);

    EXPECT_EQ(ctm.row[1].components[0], 0);
    EXPECT_EQ(ctm.row[1].components[1], 0);
    EXPECT_EQ(ctm.row[1].components[2], 0);
    EXPECT_EQ(ctm.row[1].components[3], 0);
    
    EXPECT_EQ(ctm.row[2].components[0], 0);
    EXPECT_EQ(ctm.row[2].components[1], 0);
    EXPECT_EQ(ctm.row[2].components[2], 0);
    EXPECT_EQ(ctm.row[2].components[3], 0);
    
    EXPECT_EQ(ctm.row[3].components[0], 0);
    EXPECT_EQ(ctm.row[3].components[1], 0);
    EXPECT_EQ(ctm.row[3].components[2], 0);
    EXPECT_EQ(ctm.row[3].components[3], 0);
}

TEST_F(MatrixStackTest, TranslateScale) {
    matStack->initialize();
    matStack->translate(1.5,2.5,3.5);
    matStack->scale(2,2,2);

    TransformMatrix ctm = matStack->get_ctm();
    EXPECT_EQ(ctm.row[0].components[0], 0);
    EXPECT_EQ(ctm.row[0].components[1], 0);
    EXPECT_EQ(ctm.row[0].components[2], 0);
    EXPECT_EQ(ctm.row[0].components[3], 0);

    EXPECT_EQ(ctm.row[1].components[0], 0);
    EXPECT_EQ(ctm.row[1].components[1], 0);
    EXPECT_EQ(ctm.row[1].components[2], 0);
    EXPECT_EQ(ctm.row[1].components[3], 0);
    
    EXPECT_EQ(ctm.row[2].components[0], 0);
    EXPECT_EQ(ctm.row[2].components[1], 0);
    EXPECT_EQ(ctm.row[2].components[2], 0);
    EXPECT_EQ(ctm.row[2].components[3], 0);
    
    EXPECT_EQ(ctm.row[3].components[0], 0);
    EXPECT_EQ(ctm.row[3].components[1], 0);
    EXPECT_EQ(ctm.row[3].components[2], 0);
    EXPECT_EQ(ctm.row[3].components[3], 0);
}

TEST_F(MatrixStackTest, ScaleTranslate) {
    matStack->initialize();
    matStack->scale(2,2,2);
    matStack->translate(1.5,2.5,3.5);

    TransformMatrix ctm = matStack->get_ctm();
    EXPECT_EQ(ctm.row[0].components[0], 0);
    EXPECT_EQ(ctm.row[0].components[1], 0);
    EXPECT_EQ(ctm.row[0].components[2], 0);
    EXPECT_EQ(ctm.row[0].components[3], 0);

    EXPECT_EQ(ctm.row[1].components[0], 0);
    EXPECT_EQ(ctm.row[1].components[1], 0);
    EXPECT_EQ(ctm.row[1].components[2], 0);
    EXPECT_EQ(ctm.row[1].components[3], 0);
    
    EXPECT_EQ(ctm.row[2].components[0], 0);
    EXPECT_EQ(ctm.row[2].components[1], 0);
    EXPECT_EQ(ctm.row[2].components[2], 0);
    EXPECT_EQ(ctm.row[2].components[3], 0);
    
    EXPECT_EQ(ctm.row[3].components[0], 0);
    EXPECT_EQ(ctm.row[3].components[1], 0);
    EXPECT_EQ(ctm.row[3].components[2], 0);
    EXPECT_EQ(ctm.row[3].components[3], 0);
}

TEST_F(MatrixStackTest, ScalePushTranslatePop) {
    matStack->initialize();
    matStack->scale(2,2,2);
    matStack->pushMatrix();
    matStack->translate(1.5,2.5,3.5);
    matStack->print_ctm();
    matStack->popMatrix();

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

TEST_F(MatrixStackTest, InitPop) {
    matStack->initialize();
    matStack->popMatrix();

    TransformMatrix ctm = matStack->get_ctm();
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
