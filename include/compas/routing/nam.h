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
 */

#include <stdint.h>
#include <string.h>

/**
 * @brief NAM packet definition
 */
typedef struct __attribute__((packed)) {
    uint16_t name_len;          /**< Length of the name */
} compas_nam_t;

/**
 * @brief Create a PAM
 *
 * @param[out]  nam             Pointer to the NAM
 * @param[in]   name            Name to put into the NAM
 * @param[in]   name_len        Length of the name
 */
void compas_nam_set_name(compas_nam_t *nam, const char *name,
                         uint16_t name_len);
