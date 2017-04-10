/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    bool root;
    uint16_t rank;
    const char *prefix;
    uint16_t prefix_len;
} compas_mst_t;

void compas_mst_init_root(compas_mst_t *mst, const char *prefix,
                          uint16_t prefix_len);
