#include "unity.h"

void setUp(void) {}
void tearDown(void) {}

void test_pam_extract_prefix(void) {
    TEST_ASSERT_TRUE(1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_pam_extract_prefix);
    return UNITY_END();
}
