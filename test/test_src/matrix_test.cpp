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

        C = A*B;
        C.print();
        /*
        EXPECT_EQ((C.data)[0][0], 1.0);
        EXPECT_EQ((C.data)[0][1], 2.0);
        EXPECT_EQ((C.data)[0][2], 3.0);
        EXPECT_EQ((C.data)[0][3], 4.0);
        */
}
