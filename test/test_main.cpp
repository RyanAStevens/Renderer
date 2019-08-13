#include "../include/vector2.h"
#include <gtest/gtest.h>
#include <iostream>

namespace {

// The fixture for testing class Vector2.
class Vector2Test : public ::testing::Test {
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  Vector2Test() {
     // You can do set-up work for each test here.
     std::cout << "hello from Vector2Test constructor.\n";
  }

  ~Vector2Test() override {
     // You can do clean-up work that doesn't throw exceptions here.
     std::cout << "hello from Vector2Test destructor.\n";
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override {
     // Code here will be called immediately after the constructor (right
     // before each test).
     std::cout << "hello from google test SetUp().\n";
  }

  void TearDown() override {
     // Code here will be called immediately after each test (right
     // before the destructor).
     std::cout << "hello from google test TearDown().\n";
  }

  // Objects declared here can be used by all tests in the test suite for Vector2.
};

// Tests the Vector2 '+' operator.
TEST_F(Vector2Test, Vector2PlusOperator) {
  Vector2 A = Vector2(2.0, 1.0);
  Vector2 B = Vector2(3.0, 1.0);
  Vector2 C = A+B;
  EXPECT_EQ(C.components[0],5.0);
  EXPECT_EQ(C.components[1],2.0);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
