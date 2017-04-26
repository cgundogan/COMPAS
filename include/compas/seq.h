/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file seq.h
 * @brief Serial Number Arithmetic (RFC 1982)
 * @author Cenk Gündoğan <mail-github@cgundogan.de>
 * @copyright GNU Lesser General Public License v2.1
 */

#ifndef COMPAS_SEQ_H
#define COMPAS_SEQ_H

#include <stdint.h>
#include <errno.h>

/**
 * @brief 8 bit sequence number
 */
typedef uint8_t compas_seq8_t;

/**
 * @brief Addition of a 8 bit sequence number @p s and a positive integer @p n
 * in the serial number space UINT8_MAX
 * @see <a href="https://tools.ietf.org/html/rfc1982#section-3.1">
 *      3.1. Addition
 * </a>
 *
 * @param[in]       s       sequence number
 * @param[in]       n       positive integer in the range of [0 .. 127]
 * @return          s + n, if valid
 * @return          s, if n is out of range
 */
compas_seq8_t compas_seq8_add(compas_seq8_t s, uint8_t n);

/**
 * @brief Compare sequence numbers @p s1, @p s2 in the serial number space UINT8_MAX
 * @see <a href="https://tools.ietf.org/html/rfc1982#section-3.2">
 *      3.2. Comparison
 * </a>
 * @param[in]       s1      first sequence number
 * @param[in]       s2      second sequence number
 * @return          -1, if s1 < s2
 * @return          0, if s1 == s2
 * @return          1, if s1 > s2
 * @return          -EINVAL, if comparison of the pair (s1,s2) is undefined
 */
int compas_seq8_cmp(compas_seq8_t s1, compas_seq8_t s2);

#endif /* COMPAS_SEQ_H */
