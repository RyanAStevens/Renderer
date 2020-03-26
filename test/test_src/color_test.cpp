#include <color_test.h>
#include <color.h>

ColorTest::ColorTest() {
//    std::cout << "hello from ColorTest constructor.\n";
}

ColorTest::~ColorTest() {
//    std::cout << "hello from ColorTest destructor.\n";
}

void ColorTest::SetUp() {
//    std::cout << "hello from ColorTest SetUp().\n";
}

void ColorTest::TearDown() {
//    std::cout << "hello from ColorTest TearDown().\n";
}

// Tests the Color '+' operator.
TEST_F(ColorTest, ColorPlusOperator) {
  Color A = Color(2.0, 1.0, 7.0);
  Color B = Color(3.0, 1.0, 7.0);
  Color C = A+B;
  EXPECT_EQ(C.r, 5.0);
  EXPECT_EQ(C.g, 2.0);
  EXPECT_EQ(C.b, 14.0);
}

// Tests the Color '-' operator.
TEST_F(ColorTest, ColorMinusOperator) {
  Color A = Color(5.0, 3.0, 8.0);
  Color B = Color(2.0, 1.0, 6.0);
  Color C = A-B;
  EXPECT_EQ(C.r, 3.0);
  EXPECT_EQ(C.g, 2.0);
  EXPECT_EQ(C.b, 2.0);
}

// Tests the Color '*' operator.
TEST_F(ColorTest, ColorMultiplyOperator) {
  Color A = Color(5.0, 3.0, 10.0);
  Color B = Color(2.0, 2.0, 2.0);
  Color C = A*B;
  EXPECT_EQ(C.r, 10.0);
  EXPECT_EQ(C.g, 6.0);
  EXPECT_EQ(C.b, 20.0);
}

// Tests the Color scalar '*' operator.
TEST_F(ColorTest, ColorScalarMultiplyOperator) {
  Color A = Color(5.0, 3.0, 10.0);
  Color B = A*2.0;
  EXPECT_EQ(B.r, 10.0);
  EXPECT_EQ(B.g, 6.0);
  EXPECT_EQ(B.b, 20.0);
}

// Tests the Color '/' operator.
TEST_F(ColorTest, ColorScalarDivisionOperator) {
  Color A = Color(6.0, 12.0, 8.0);
  Color B = A/2.0;
  EXPECT_EQ(B.r, 3.0);
  EXPECT_EQ(B.g, 6.0);
  EXPECT_EQ(B.b, 4.0);
}
