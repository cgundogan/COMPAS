/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file pam.h
 * @brief Prefix Advertisement Message (PAM) definitions for COMPAS
 * @author Cenk Gündoğan <mail-github@cgundogan.de>
 */

#include <stdint.h>
#include <string.h>

#include "compas/routing/dodag.h"

/**
 * @brief PAM packet definition
 *
 * The name prefix follows this struct immediately.
 */
typedef struct __attribute__((packed)) {
    uint16_t rank;              /**< Rank of the sender */
    uint16_t prefix_len;        /**< Length of the prefix */
} compas_pam_t;

/**
 * @brief Create a PAM
 *
 * @param[in]   dodag           Pointer to the DODAG
 * @param[out]  pam             Pointer to the PAM to fill
 */
void compas_pam_create(compas_dodag_t *dodag, compas_pam_t *pam);

/**
 * @brief Get length of PAM
 *
 * @param[in]   dodag           Pointer to the DODAG
 *
 * @return      The length of the PAM to be created
 */
size_t compas_pam_len(compas_dodag_t *dodag);
