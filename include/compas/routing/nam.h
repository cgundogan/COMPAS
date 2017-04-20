/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file nam.h
 * @brief Name Advertisement Message (NAM) definitions for COMPAS
 * @author Cenk Gündoğan <mail-github@cgundogan.de>
 * @copyright GNU Lesser General Public License v2.1
 */

#ifndef COMPAS_ROUTING_NAM_H
#define COMPAS_ROUTING_NAM_H

#include <stdint.h>
#include <string.h>

/**
 * @brief Max. length of a name suffix
 */
#ifndef COMPAS_NAME_SUFFIX_LEN
#define COMPAS_NAME_SUFFIX_LEN  (32)
#endif

/**
 * @brief Max. length of a name
 */
#define COMPAS_NAME_LEN         (COMPAS_PREFIX_LEN + COMPAS_NAME_SUFFIX_LEN)

/**
 * @brief NAM packet definition
 * @note The name follows this struct immediately and is of length
 * compas_nam_t::name_len.
 */
typedef struct __attribute__((packed)) {
    uint8_t type;               /**< Message type of a NAM */
    uint16_t name_len;          /**< Length of the name */
} compas_nam_t;

/**
 * @brief Create a NAM in @p nam
 *
 * @param[in]   name            Name to put into the NAM
 * @param[in]   name_len        Length of the name
 * @param[out]  nam             Pointer to the NAM
 */
void compas_nam_create(const char *name, uint16_t name_len, compas_nam_t *nam);

/**
 * @brief Parse NAM @p nam
 *
 * @param[out]  name            Name in the NAM
 * @param[out]  name_len        Length of the name
 * @param[in]   nam             Pointer to NAM to parse from
 */
void compas_nam_parse(char *name, uint16_t *name_len, const compas_nam_t *nam);

#endif /* COMPAS_ROUTING_NAM_H */
