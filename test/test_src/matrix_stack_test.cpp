#include "../test_include/matrix_stack_test.h"
#include "../../include/matrix_stack.h"

MatrixStackTest::MatrixStackTest() {
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

TEST_F(MatrixStackTest, ) {
    gtInitialize()
    print_ctm()
}
    
TEST_F(MatrixStackTest, ) {
    gtInitialize()
    gtTranslate(3,2,1.5)
    print_ctm()
}

TEST_F(MatrixStackTest, ) {
    gtInitialize()
    gtScale(2,3,4)
    print_ctm()
}

TEST_F(MatrixStackTest, ) {
    gtInitialize()
    gtRotateX(90)
    print_ctm()
}

TEST_F(MatrixStackTest, ) {
    gtInitialize()
    gtRotateY(-15)
    print_ctm()
}

TEST_F(MatrixStackTest, ) {
    gtInitialize()
    gtPushMatrix()
    gtRotateZ(45)
    print_ctm()
    gtPopMatrix()
    print_ctm()
}

TEST_F(MatrixStackTest, ) {
    gtInitialize()
    gtTranslate(1.5,2.5,3.5)
    gtScale(2,2,2)
    print_ctm()
}

TEST_F(MatrixStackTest, ) {
    gtInitialize()
    gtScale(2,2,2)
    gtTranslate(1.5,2.5,3.5)
    print_ctm()
}

TEST_F(MatrixStackTest, ) {
    gtInitialize()
    gtScale(2,2,2)
    gtPushMatrix()
    gtTranslate(1.5,2.5,3.5)
    print_ctm()
    gtPopMatrix()
    print_ctm()
}

TEST_F(MatrixStackTest, ) {
    gtInitialize()
    gtPopMatrix()
}
