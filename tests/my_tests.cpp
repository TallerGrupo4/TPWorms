#include <gtest/gtest.h>

namespace {
int getNumber() { return 1; }
}  // namespace

TEST(TestTopic, GetNumber) { EXPECT_EQ(getNumber(), 1); }

TEST(TestTopic, GetNumber2Error) {
    ASSERT_EQ(getNumber(), 2) << "getNumber() should return 2";
    // No other code will be executed if the assertion fails
    // On the other hand, it it was an EXPECT_ assertion, the test would continue
}
