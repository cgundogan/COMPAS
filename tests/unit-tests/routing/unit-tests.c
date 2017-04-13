/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "unity.h"
#include "compas/routing/nam.h"
#include "compas/routing/pam.h"

void setUp(void) {}
void tearDown(void) {}

#define TEST_PREFIX_LEN (18)
static const char test_prefix[TEST_PREFIX_LEN] = "/HAW/t/te/tes/test";
static char buf[sizeof(compas_pam_t) + TEST_PREFIX_LEN];

void test_compas_dodag_init_root(void)
{
    compas_dodag_t dodag;
    compas_dodag_init_root(&dodag, test_prefix, TEST_PREFIX_LEN);
    TEST_ASSERT_EQUAL_UINT16(dodag.rank, COMPAS_DODAG_ROOT_RANK);
    TEST_ASSERT_EQUAL_UINT16(dodag.prefix_len, TEST_PREFIX_LEN);
    TEST_ASSERT_EQUAL_STRING_LEN(dodag.prefix, test_prefix, TEST_PREFIX_LEN);
}

void test_compas_pam_set_prefix(void)
{
    compas_dodag_t dodag;
    compas_dodag_init_root(&dodag, test_prefix, TEST_PREFIX_LEN);
    compas_pam_t *pam = (compas_pam_t *) buf;
    compas_pam_set_prefix(&dodag, pam);
    TEST_ASSERT_EQUAL_UINT16(pam->prefix_len, TEST_PREFIX_LEN);
    TEST_ASSERT_EQUAL_STRING_LEN((char *) (pam + 1), test_prefix, TEST_PREFIX_LEN);
}

void test_compas_pam_create(void)
{
    compas_dodag_t dodag;
    compas_dodag_init_root(&dodag, test_prefix, TEST_PREFIX_LEN);
    compas_pam_t *pam = (compas_pam_t *) buf;
    compas_pam_create(&dodag, pam);
    TEST_ASSERT_EQUAL_UINT16(pam->prefix_len, TEST_PREFIX_LEN);
    TEST_ASSERT_EQUAL_STRING_LEN((char *) (pam + 1), test_prefix, TEST_PREFIX_LEN);
}

void test_compas_nam_set_name(void)
{
    compas_nam_t *nam = (compas_nam_t *) buf;
    compas_nam_set_name(nam, test_prefix, TEST_PREFIX_LEN);
    TEST_ASSERT_EQUAL_UINT16(nam->name_len, TEST_PREFIX_LEN);
    TEST_ASSERT_EQUAL_STRING_LEN((char *) (nam + 1), test_prefix, TEST_PREFIX_LEN);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_compas_dodag_init_root);
    RUN_TEST(test_compas_pam_set_prefix);
    RUN_TEST(test_compas_pam_create);
    RUN_TEST(test_compas_nam_set_name);
    return UNITY_END();
}
