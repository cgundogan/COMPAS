/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdint.h>

#define COMPAS_DODAG_ROOT_RANK      (1)

typedef struct {
    uint16_t rank;
    const char *prefix;
    uint16_t prefix_len;
} compas_dodag_t;

void compas_dodag_init_root(compas_dodag_t *dodag, const char *prefix,
                            uint16_t prefix_len);
