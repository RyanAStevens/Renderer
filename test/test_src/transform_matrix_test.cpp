#include "../test_include/transform_matrix_test.h"
#include "../../include/transform_matrix.h"

Transform_MatrixTest::Transform_MatrixTest() {
//    std::cout << "hello from Transform_MatrixTest constructor.\n";
}

Transform_MatrixTest::~Transform_MatrixTest() {
//    std::cout << "hello from Transform_MatrixTest destructor.\n";
}

void Transform_MatrixTest::SetUp() {
//    std::cout << "hello from google test SetUp().\n";
}

void Transform_MatrixTest::TearDown() {
//    std::cout << "hello from google test TearDown().\n";
}

// Tests the Transform_Matrix '*' operator.
TEST_F(Transform_MatrixTest, Transform_MatrixMultiplyOperator) {
  Transform_Matrix A = Transform_Matrix();
  Transform_Matrix B = Transform_Matrix(Vector3H(1.0, 2.0, 3.0, 4.0),
                                       Vector3H(1.0, 2.0, 3.0, 4.0),
                                       Vector3H(1.0, 2.0, 3.0, 4.0),
                                       Vector3H(1.0, 2.0, 3.0, 4.0));
  Transform_Matrix C = A*B;
  //row 0
  EXPECT_EQ(C.row[0].components[0], 1.0);
  EXPECT_EQ(C.row[0].components[1], 2.0);
  EXPECT_EQ(C.row[0].components[2], 3.0);
  EXPECT_EQ(C.row[0].components[3], 4.0);
}
