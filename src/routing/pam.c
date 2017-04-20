/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <string.h>

#include "compas/debug.h"
#include "compas/routing/pam.h"

void compas_pam_create(const compas_dodag_t *dodag, compas_pam_t *pam)
{
    pam->type = COMPAS_MSG_TYPE_PAM;
    pam->rank = dodag->rank;
    pam->prefix_len = dodag->prefix_len;
    memcpy(pam + 1, dodag->prefix, dodag->prefix_len);
}

size_t compas_pam_len(const compas_dodag_t *dodag)
{
    size_t len = 0;
    len  += sizeof(compas_pam_t);
    len  += dodag->prefix_len;
    return len;
}

int compas_pam_parse(compas_dodag_t *dodag, const compas_pam_t *pam,
                     const uint8_t *face_addr, uint8_t face_addr_len)
{
    if (pam->rank == UINT16_MAX) {
        CDBG_PRINT("compas_pam_parse: ignore PAM with max rank\n");
        return -1;
    }

    if ((dodag->rank != COMPAS_DODAG_UNDEF) && (pam->rank + 1) >= dodag->rank) {
        CDBG_PRINT("compas_pam_parse: ignore PAM of higher or equal rank\n");
        return -2;
    }

    dodag->rank = pam->rank + 1;
    dodag->prefix_len = pam->prefix_len;
    memcpy(dodag->prefix, (char *) (pam + 1), pam->prefix_len);

    dodag->parent.face_addr_len = face_addr_len;
    memcpy(dodag->parent.face_addr, face_addr,
           (face_addr_len < COMPAS_FACE_ADDR_LEN) ?
            face_addr_len : COMPAS_FACE_ADDR_LEN);

    return 0;
}
