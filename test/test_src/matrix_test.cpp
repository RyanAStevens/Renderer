#include <matrix.h>
#include <matrix_test.h>

MatrixTest::MatrixTest() {
//    std::cout << "hello from MatrixTest constructor.\n";
}

MatrixTest::~MatrixTest() {
//    std::cout << "hello from MatrixTest destructor.\n";
}

void MatrixTest::SetUp() {
//    std::cout << "hello from google test SetUp().\n";
}

void MatrixTest::TearDown() {
//    std::cout << "hello from google test TearDown().\n";
}

// Tests the Matrix '*' operator.
TEST_F(MatrixTest, MatrixMultiplyOperator) {


                    Matrix A(4);
                    Matrix B(1);
                    Matrix C(1);
                    A[0][0] = 1.0;
                    A[1][1] = 1.0;
                    A[2][2] = 1.0;
                    A[3][3] = 1.0;
                    
                    B[0][0] = 1.0;
                    B[0][1] = 2.0;
                    B[0][2] = 3.0;
                    B[0][3] = 4.0;

				    printf("main:::before A.print();\n");
                    A.print();
				    printf("main:::before B.print();\n");
                    B.print();
				    printf("main:::before C = A*B;\n");
                     C = A*B;
				    printf("main:::before (A*B).print();\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                    (A*B).print();
				   //printf("before C.print();\n");
                   // C.print();


/*
Matrix A = Matrix();
  Matrix B = Matrix(Vector3H(1.0, 2.0, 3.0, 4.0),
                    Vector3H(1.0, 2.0, 3.0, 4.0),
                    Vector3H(1.0, 2.0, 3.0, 4.0),
                    Vector3H(1.0, 2.0, 3.0, 4.0));
  A.print();
  //B.print();
  Matrix C = A*B;
  //C.print();
  //row 0
  EXPECT_EQ((*C.data)[0][0], 1.0);
  EXPECT_EQ((*C.data)[0][1], 2.0);
  EXPECT_EQ((*C.data)[0][2], 3.0);
  EXPECT_EQ((*C.data)[0][3], 4.0);
  */
}
