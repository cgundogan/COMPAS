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
    dodag->sol_num = 0;
    dodag->rank = COMPAS_DODAG_ROOT_RANK;
    compas_prefix_init(&dodag->prefix, prefix, prefix_len);
    memset(&dodag->parent, 0, sizeof(compas_parent_t));
}

bool compas_dodag_parent_eq(const compas_dodag_t *dodag,
                            const compas_face_t *face)
{
    uint8_t len = (face->face_addr_len <= dodag->parent.face.face_addr_len) ?
                   face->face_addr_len : dodag->parent.face.face_addr_len;
    return memcmp(dodag->parent.face.face_addr, face->face_addr, len) == 0;
}

void compas_dodag_print(const compas_dodag_t *dodag)
{
    CDBG_PRINT("rank: %u - prefix: %.*s - prefix_len: %u - ",
               (unsigned) dodag->rank, dodag->prefix.prefix_len,
               dodag->prefix.prefix, (unsigned) dodag->prefix.prefix_len);

    CDBG_PRINT("parent_addr_len: %u - parent_addr: ",
               (unsigned) dodag->parent.face.face_addr_len);

    unsigned i;
    for (i = 0; i < dodag->parent.face.face_addr_len; i++) {
        CDBG_PRINT("%02x ", dodag->parent.face.face_addr[i]);
    }

    CDBG_PRINT("\n");
}
