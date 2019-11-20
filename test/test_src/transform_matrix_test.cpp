#include <transform_matrix.h>
#include <transform_matrix_test.h>

TransformMatrixTest::TransformMatrixTest() {
//    std::cout << "hello from TransformMatrixTest constructor.\n";
}

TransformMatrixTest::~TransformMatrixTest() {
//    std::cout << "hello from TransformMatrixTest destructor.\n";
}

void TransformMatrixTest::SetUp() {
//    std::cout << "hello from google test SetUp().\n";
}

void TransformMatrixTest::TearDown() {
//    std::cout << "hello from google test TearDown().\n";
}

// Tests the TransformMatrix '*' operator.
TEST_F(TransformMatrixTest, TransformMatrixMultiplyOperator) {
  TransformMatrix A = TransformMatrix();
  TransformMatrix B = TransformMatrix(Vector3H(1.0, 2.0, 3.0, 4.0),
                                       Vector3H(1.0, 2.0, 3.0, 4.0),
                                       Vector3H(1.0, 2.0, 3.0, 4.0),
                                       Vector3H(1.0, 2.0, 3.0, 4.0));
  TransformMatrix C = A*B;
  //row 0
  EXPECT_EQ(C.row[0].components[0], 1.0);
  EXPECT_EQ(C.row[0].components[1], 2.0);
  EXPECT_EQ(C.row[0].components[2], 3.0);
  EXPECT_EQ(C.row[0].components[3], 4.0);
}
