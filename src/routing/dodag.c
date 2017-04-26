/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <string.h>

#include "compas/debug.h"
#include "compas/routing/dodag.h"

void compas_dodag_init_root(compas_dodag_t *dodag, const char *prefix,
                            uint16_t prefix_len)
{
    dodag->freshness = 0;
    dodag->flags = 0;
    dodag->rank = COMPAS_DODAG_ROOT_RANK;
    memcpy(dodag->prefix, prefix,
           (prefix_len < COMPAS_PREFIX_LEN) ? prefix_len : COMPAS_PREFIX_LEN);
    dodag->prefix_len = prefix_len;
    memset(&dodag->parent, 0, sizeof(compas_parent_t));
}

bool compas_dodag_parent_eq(compas_dodag_t *dodag, const uint8_t *face_addr,
                            uint8_t face_addr_len) {
    uint8_t len = (face_addr_len <= dodag->parent.face_addr_len) ?
                   face_addr_len : dodag->parent.face_addr_len;
    return memcmp(dodag->parent.face_addr, face_addr, len) == 0;
}

void compas_dodag_print(compas_dodag_t *dodag)
{
    CDBG_PRINT("rank: %u - prefix: %.*s - prefix_len: %u - ",
               (unsigned) dodag->rank, dodag->prefix_len, dodag->prefix,
               (unsigned) dodag->prefix_len);

    CDBG_PRINT("parent_addr_len: %u - parent_addr: ", (unsigned) dodag->parent.face_addr_len);

    for (unsigned i = 0; i < dodag->parent.face_addr_len; i++) {
        CDBG_PRINT("%02x ", dodag->parent.face_addr[i]);
    }

    CDBG_PRINT("\n");
}
