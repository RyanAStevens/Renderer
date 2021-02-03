#include <gtest/gtest.h>

// The fixture for testing class Matrix.
class MatrixTest : public ::testing::Test {
protected:
  MatrixTest();
  ~MatrixTest() override;
  void SetUp() override;
  void TearDown() override;
};
