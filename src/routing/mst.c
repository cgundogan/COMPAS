/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "routing/mst.h"

void compas_mst_init_root(compas_mst_t *mst, const char *prefix,
                          uint16_t prefix_len)
{
    mst->root = true;
    mst->rank = 0;
    mst->prefix = prefix;
    mst->prefix_len = prefix_len;
}
