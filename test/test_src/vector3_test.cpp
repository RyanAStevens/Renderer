#include "../test_include/vector3_test.h"
#include "../../include/vector3.h"

Vector3Test::Vector3Test() {
//    std::cout << "hello from Vector3Test constructor.\n";
}

Vector3Test::~Vector3Test() {
//    std::cout << "hello from Vector3Test destructor.\n";
}

void Vector3Test::SetUp() {
//    std::cout << "hello from google test SetUp().\n";
}

void Vector3Test::TearDown() {
//    std::cout << "hello from google test TearDown().\n";
}

// Tests the Vector3 '+' operator.
TEST_F(Vector3Test, Vector3PlusOperator) {
  Vector3 A = Vector3(2.0, 1.0, 7.0);
  Vector3 B = Vector3(3.0, 1.0, 7.0);
  Vector3 C = A+B;
  EXPECT_EQ(C.components[0], 5.0);
  EXPECT_EQ(C.components[1], 2.0);
  EXPECT_EQ(C.components[2], 14.0);
}

// Tests the Vector3 '-' operator.
TEST_F(Vector3Test, Vector3MinusOperator) {
  Vector3 A = Vector3(5.0, 3.0, 8.0);
  Vector3 B = Vector3(2.0, 1.0, 6.0);
  Vector3 C = A-B;
  EXPECT_EQ(C.components[0], 3.0);
  EXPECT_EQ(C.components[1], 2.0);
  EXPECT_EQ(C.components[2], 2.0);
}

// Tests the Vector3 '*' operator.
TEST_F(Vector3Test, Vector3ScalarMultiplyOperator) {
  Vector3 A = Vector3(5.0, 3.0, 10.0);
  Vector3 B = A*2.0;
  EXPECT_EQ(B.components[0], 10.0);
  EXPECT_EQ(B.components[1], 6.0);
  EXPECT_EQ(B.components[2], 20.0);
}

// Tests the Vector3 '/' operator.
TEST_F(Vector3Test, Vector3ScalarDivisionOperator) {
  Vector3 A = Vector3(6.0, 12.0, 8.0);
  Vector3 B = A/2.0;
  EXPECT_EQ(B.components[0], 3.0);
  EXPECT_EQ(B.components[1], 6.0);
  EXPECT_EQ(B.components[2], 4.0);
}

// Tests the Vector3 dot product.
TEST_F(Vector3Test, Vector3dotProduct) {
  Vector3 A = Vector3(1.0, 2.0, 3.0);
  Vector3 B = Vector3(1.0, 5.0, 7.0);
  EXPECT_EQ(32.0, A.dot(B));
}

// Tests the Vector3 cross product.
TEST_F(Vector3Test, Vector3crossProduct) {
  Vector3 A = Vector3(1.0, 2.0, 3.0);
  Vector3 B = Vector3(1.0, 5.0, 7.0);
  Vector3 C = A.cross(B);
  EXPECT_EQ(C.components[0], -1.0);
  EXPECT_EQ(C.components[1], -4.0);
  EXPECT_EQ(C.components[2], 3.0);
}
