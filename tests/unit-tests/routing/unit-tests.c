#include "unity.h"
#include "routing/pam.h"

void setUp(void) {}
void tearDown(void) {}

#define TEST_PREFIX_LEN (18)
static const char test_prefix[TEST_PREFIX_LEN] = "/HAW/t/te/tes/test";
static char buf[sizeof(routing_pam_t) + TEST_PREFIX_LEN];

void test_pam_set_prefix(void) {
    routing_pam_t *pam = (routing_pam_t *) buf;
    routing_pam_set_prefix(pam, test_prefix, strlen(test_prefix));
    TEST_ASSERT_EQUAL_UINT16(pam->prefix_len, TEST_PREFIX_LEN);
    TEST_ASSERT_EQUAL_STRING_LEN((char *) (pam + 1), test_prefix, TEST_PREFIX_LEN);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_pam_set_prefix);
    return UNITY_END();
}
