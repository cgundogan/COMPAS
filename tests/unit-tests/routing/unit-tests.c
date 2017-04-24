/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <string.h>

#include "unity.h"
#include "compas/routing/nam.h"
#include "compas/routing/pam.h"

#define TEST_PREFIX_LEN (18)
static const char test_prefix[TEST_PREFIX_LEN] = "/HAW/t/te/tes/test";
static char buf_pam[sizeof(compas_pam_t) + TEST_PREFIX_LEN];
static char buf_nam[sizeof(compas_nam_t) + 3 * sizeof(compas_tlv_t) + \
                    sizeof(uint16_t) + 2 * TEST_PREFIX_LEN];
static const uint8_t face_addr[] = { 0x00, 0x01, 0x02, 0x03, \
                                     0x04, 0x05, 0x06, 0x07 };

void setUp(void) {
    memset(buf_pam, 0, sizeof(buf_pam));
    memset(buf_nam, 0, sizeof(buf_nam));
}

void tearDown(void) {}

void test_compas_dodag_init_root(void)
{
    compas_dodag_t dodag;
    compas_dodag_init_root(&dodag, test_prefix, TEST_PREFIX_LEN);
    TEST_ASSERT_EQUAL_UINT16(dodag.rank, COMPAS_DODAG_ROOT_RANK);
    TEST_ASSERT_EQUAL_UINT16(dodag.prefix_len, TEST_PREFIX_LEN);
    TEST_ASSERT_EQUAL_STRING_LEN(dodag.prefix, test_prefix, TEST_PREFIX_LEN);
}

void test_compas_pam_create(void)
{
    compas_dodag_t dodag;
    compas_dodag_init_root(&dodag, test_prefix, TEST_PREFIX_LEN);
    compas_pam_t *pam = (compas_pam_t *) buf_pam;
    compas_pam_create(&dodag, pam);
    TEST_ASSERT_EQUAL_UINT8(pam->type, COMPAS_MSG_TYPE_PAM);
    TEST_ASSERT_EQUAL_UINT16(pam->rank, COMPAS_DODAG_ROOT_RANK);
    TEST_ASSERT_EQUAL_UINT16(pam->prefix_len, TEST_PREFIX_LEN);
    TEST_ASSERT_EQUAL_STRING_LEN((char *) (pam + 1), test_prefix, TEST_PREFIX_LEN);
}

void test_compas_pam_len(void)
{
    compas_dodag_t dodag;
    compas_dodag_init_root(&dodag, test_prefix, TEST_PREFIX_LEN);
    compas_pam_t *pam = (compas_pam_t *) buf_pam;
    size_t len = compas_pam_len(&dodag);
    TEST_ASSERT_EQUAL_UINT(len, TEST_PREFIX_LEN + sizeof(compas_pam_t));
}

void test_compas_pam_parse(void)
{
    compas_dodag_t dodag1;
    compas_dodag_t dodag2;
    compas_dodag_init_root(&dodag1, test_prefix, TEST_PREFIX_LEN);
    compas_pam_t *pam = (compas_pam_t *) buf_pam;
    compas_pam_create(&dodag1, pam);
    uint8_t face_addr_len = sizeof(face_addr)/sizeof(face_addr[0]);
    TEST_ASSERT_EQUAL_INT(0, compas_pam_parse(&dodag2, pam,
                                              face_addr, face_addr_len));
    TEST_ASSERT_EQUAL_UINT16(dodag1.prefix_len, dodag2.prefix_len);
    TEST_ASSERT_EQUAL_STRING_LEN(dodag1.prefix, dodag2.prefix, dodag1.prefix_len);
    TEST_ASSERT_EQUAL_UINT16(dodag1.rank + 1, dodag2.rank);
    TEST_ASSERT_EQUAL_UINT8(face_addr_len, dodag2.parent.face_addr_len);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(face_addr, dodag2.parent.face_addr, face_addr_len);
    TEST_ASSERT_EQUAL_INT(-2, compas_pam_parse(&dodag2, pam,
                                               face_addr, face_addr_len));
    memset(&dodag2, 0, sizeof(dodag2));
    pam->rank = UINT16_MAX;
    TEST_ASSERT_EQUAL_INT(-1, compas_pam_parse(&dodag2, pam,
                                               face_addr, face_addr_len));
}

void test_compas_nam_create(void)
{
    compas_nam_t *nam = (compas_nam_t *) buf_nam;
    compas_nam_create(nam);
    TEST_ASSERT_EQUAL_UINT8(nam->type, COMPAS_MSG_TYPE_NAM);
    TEST_ASSERT_EQUAL_UINT16(0, nam->len);
}

void test_compas_nam_tlv_add_name(void)
{
    compas_nam_t *nam = (compas_nam_t *) buf_nam;
    compas_nam_create(nam);
    compas_nam_tlv_add_name(nam, test_prefix, TEST_PREFIX_LEN);
    TEST_ASSERT_EQUAL_UINT16(sizeof(compas_tlv_t) + TEST_PREFIX_LEN, nam->len);
    compas_nam_tlv_add_name(nam, test_prefix, TEST_PREFIX_LEN);
    TEST_ASSERT_EQUAL_UINT16(2 * sizeof(compas_tlv_t) + 2 * TEST_PREFIX_LEN,
                             nam->len);
}

void test_compas_nam_tlv_add_lifetime(void)
{
    compas_nam_t *nam = (compas_nam_t *) buf_nam;
    compas_nam_create(nam);
    compas_nam_tlv_add_lifetime(nam, 100U);
    TEST_ASSERT_EQUAL_UINT16(sizeof(compas_tlv_t) + sizeof(uint16_t), nam->len);
}

void test_compas_nam_tlv_iter(void)
{
    compas_nam_t *nam = (compas_nam_t *) buf_nam;
    compas_nam_create(nam);
    compas_nam_tlv_add_lifetime(nam, 100U);
    compas_nam_tlv_add_name(nam, test_prefix, TEST_PREFIX_LEN);
    compas_nam_tlv_add_name(nam, test_prefix, TEST_PREFIX_LEN);
    TEST_ASSERT_EQUAL_UINT16(3 * sizeof(compas_tlv_t) + sizeof(uint16_t) +
                             2 * TEST_PREFIX_LEN, nam->len);
    uint16_t offset = 0;
    compas_tlv_t *tlv;
    TEST_ASSERT_TRUE(compas_nam_tlv_iter(nam, &offset, &tlv));
    TEST_ASSERT_EQUAL_UINT8(COMPAS_TLV_LIFETIME, tlv->type);
    TEST_ASSERT_EQUAL_UINT16(sizeof(compas_tlv_t) + sizeof(uint16_t), offset);
    TEST_ASSERT_TRUE(compas_nam_tlv_iter(nam, &offset, &tlv));
    TEST_ASSERT_EQUAL_UINT8(COMPAS_TLV_NAME, tlv->type);
    TEST_ASSERT_TRUE(compas_nam_tlv_iter(nam, &offset, &tlv));
    TEST_ASSERT_EQUAL_UINT8(COMPAS_TLV_NAME, tlv->type);
    TEST_ASSERT_FALSE(compas_nam_tlv_iter(nam, &offset, &tlv));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_compas_dodag_init_root);
    RUN_TEST(test_compas_pam_create);
    RUN_TEST(test_compas_pam_len);
    RUN_TEST(test_compas_pam_parse);
    RUN_TEST(test_compas_nam_create);
    RUN_TEST(test_compas_nam_tlv_add_name);
    RUN_TEST(test_compas_nam_tlv_add_lifetime);
    RUN_TEST(test_compas_nam_tlv_iter);
    return UNITY_END();
}
