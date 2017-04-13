/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file dodag.h
 * @brief DODAG definitions for COMPAS
 * @author Cenk Gündoğan <mail-github@cgundogan.de>
 */

#include <stdint.h>

/**
 * @brief Rank of the DODAG root
 */
#define COMPAS_DODAG_ROOT_RANK      (1)

/**
 * @brief DODAG definition
 */
typedef struct {
    uint16_t rank;              /**< Rank of the node */
    const char *prefix;         /**< Default prefix of this DODAG */
    uint16_t prefix_len;        /**< Length of the default prefix */
} compas_dodag_t;

/**
 * @brief Initialize DODAG root
 *
 * @param[in]   dodag           Pointer to the DODAG
 * @param[in]   prefix          Default prefix of the DODAG
 * @param[in]   prefix_len      Length of the prefix
 */
void compas_dodag_init_root(compas_dodag_t *dodag, const char *prefix,
                            uint16_t prefix_len);
