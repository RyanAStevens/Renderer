#include <vector2_test.h>
#include <vector2.h>

Vector2Test::Vector2Test() {
//    std::cout << "hello from Vector2Test constructor.\n";
}

Vector2Test::~Vector2Test() {
//    std::cout << "hello from Vector2Test destructor.\n";
}

void Vector2Test::SetUp() {
//    std::cout << "hello from google test SetUp().\n";
}

void Vector2Test::TearDown() {
//    std::cout << "hello from google test TearDown().\n";
}

// Tests the Vector2 '+' operator.
TEST_F(Vector2Test, Vector2PlusOperator) {
  Vector2 A = Vector2(2.0, 1.0);
  Vector2 B = Vector2(3.0, 1.0);
  Vector2 C = A+B;
  EXPECT_EQ(C.components[0],5.0);
  EXPECT_EQ(C.components[1],2.0);
}

// Tests the Vector2 '-' operator.
TEST_F(Vector2Test, Vector2MinusOperator) {
  Vector2 A = Vector2(5.0, 3.0);
  Vector2 B = Vector2(2.0, 1.0);
  Vector2 C = A-B;
  EXPECT_EQ(C.components[0],3.0);
  EXPECT_EQ(C.components[1],2.0);
}

// Tests the Vector2 '*' operator.
TEST_F(Vector2Test, Vector2ScalarMultiplyOperator) {
  Vector2 A = Vector2(5.0, 3.0);
  Vector2 B = A*2.0;
  EXPECT_EQ(B.components[0],10.0);
  EXPECT_EQ(B.components[1],6.0);
}

// Tests the Vector2 '/' operator.
TEST_F(Vector2Test, Vector2ScalarDivisionOperator) {
  Vector2 A = Vector2(6.0, 12.0);
  Vector2 B = A/2.0;
  EXPECT_EQ(B.components[0],3.0);
  EXPECT_EQ(B.components[1],6.0);
}

// Tests the Vector2 dot product.
TEST_F(Vector2Test, Vector2dotProduct) {
  Vector2 A = Vector2(5.0, 3.0);
  Vector2 B = Vector2(2.0, 1.0);
  EXPECT_EQ(13.0, A.dot(B));
}

// Tests the Vector2 cross product.
TEST_F(Vector2Test, Vector2crossProduct) {
  Vector2 A = Vector2(5.0, 3.0);
  Vector2 B = Vector2(2.0, 1.0);
  EXPECT_EQ(-1.0, A.cross(B));
}
