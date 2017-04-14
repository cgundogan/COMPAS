/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <string.h>

#include "compas/routing/dodag.h"

void compas_dodag_init_root(compas_dodag_t *dodag, const char *prefix,
                            uint16_t prefix_len)
{
    dodag->rank = COMPAS_DODAG_ROOT_RANK;
    memcpy(dodag->prefix, prefix,
           (prefix_len < COMPAS_PREFIX_LEN) ? prefix_len : COMPAS_PREFIX_LEN);
    dodag->prefix_len = prefix_len;
    memset(&dodag->parent, 0, sizeof(compas_parent_t));
}
