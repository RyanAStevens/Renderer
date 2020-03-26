#include <gtest/gtest.h>

// The fixture for testing class Color.
class ColorTest : public ::testing::Test {
protected:
  ColorTest();
  ~ColorTest() override;
  void SetUp() override;
  void TearDown() override;
};
