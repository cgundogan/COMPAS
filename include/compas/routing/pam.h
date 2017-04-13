/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdint.h>
#include <string.h>

#include "compas/routing/dodag.h"

typedef struct __attribute__((packed)) {
    uint16_t prefix_len;        /**< length of the prefix in bytes */
} compas_pam_t;

void compas_pam_create(compas_dodag_t *dodag, compas_pam_t *pam);
size_t compas_pam_len(compas_dodag_t *dodag);
void compas_pam_set_prefix(compas_dodag_t *dodag, compas_pam_t *pam);
