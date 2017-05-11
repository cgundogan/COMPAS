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
    pam->freshness = dodag->freshness;
    pam->type = COMPAS_MSG_TYPE_PAM;
    pam->rank = dodag->rank;
    pam->prefix_len = dodag->prefix.prefix_len;
    memcpy(pam + 1, dodag->prefix.prefix, dodag->prefix.prefix_len);
}

size_t compas_pam_len(const compas_dodag_t *dodag)
{
    size_t len = 0;
    len  += sizeof(compas_pam_t);
    len  += dodag->prefix.prefix_len;
    return len;
}

int compas_pam_check(const compas_dodag_t *dodag, const compas_pam_t *pam,
                     const compas_face_t *face)
{
    if (dodag->rank == COMPAS_DODAG_ROOT_RANK) {
        CDBG_PRINT("compas_pam_parse: ignore PAM for root\n");
        return COMPAS_PAM_RET_CODE_ROOTRANK;
    }

    if (pam->rank == UINT16_MAX) {
        CDBG_PRINT("compas_pam_parse: ignore PAM with max rank\n");
        return COMPAS_PAM_RET_CODE_MAXRANK;
    }

    bool is_my_parent = false;

    /* join DODAG if not joined yet */
    if (dodag->rank == COMPAS_DODAG_UNDEF) {
        return COMPAS_PAM_RET_CODE_NEWPARENT;
    }

    is_my_parent = compas_dodag_parent_eq(dodag, face);

    /* if not currently selected parent, then perform checks */
    if (!is_my_parent) {
        /* both DODAGS are equally either floating or grounded */
        if (compas_dodag_floating(dodag->flags) ==
            compas_dodag_floating(pam->flags)) {
            if (compas_seq8_cmp(dodag->freshness, pam->freshness) > 0) {
                CDBG_PRINT("compas_pam_parse: ignore outdated DODAG\n");
                return COMPAS_PAM_RET_CODE_OLDDODAG;
            }
            /* check if freshness is in range */
            if (compas_seq8_cmp(compas_seq8_add(dodag->freshness, 3),
                                pam->freshness) > 0) {
                if (dodag->rank <= (pam->rank + 1)) {
                    CDBG_PRINT("compas_pam_parse: ignore worse ranks\n");
                    return COMPAS_PAM_RET_CODE_WORSERANK;
                }
            }
        }
        /* I am not floating, neighbor is */
        else if (!compas_dodag_floating(dodag->flags)) {
            CDBG_PRINT("compas_pam_parse: ignore floating DODAG\n");
            return COMPAS_PAM_RET_CODE_FLOATINGDODAG;
        }

        /* I am floating, neighbor isn't */

        /* TODO
        else {
            if (dodag->rank <= (pam->rank + 1)) {
                CDBG_PRINT("compas_pam_parse: ignore worse ranks\n");
                return COMPAS_PAM_RET_CODE_WORSERANK;
            }
        }
        */

        /* new parent */
        return COMPAS_PAM_RET_CODE_NEWPARENT;
    }

    /* current parent */
    return COMPAS_PAM_RET_CODE_CURRPARENT;
}

int compas_pam_parse(compas_dodag_t *dodag, const compas_pam_t *pam,
                     const uint8_t *face_addr, uint8_t face_addr_len)
{
    compas_face_t face;
    compas_face_init(&face, face_addr, face_addr_len);
    int res = compas_pam_check(dodag, pam, &face);

    if ((res == COMPAS_PAM_RET_CODE_CURRPARENT) ||
        (res == COMPAS_PAM_RET_CODE_NEWPARENT)) {
        dodag->flags = pam->flags;
        dodag->freshness = pam->freshness;
        dodag->rank = pam->rank + 1;
        compas_prefix_init(&dodag->prefix, (char *) (pam + 1), pam->prefix_len);
        compas_face_init(&dodag->parent.face, face_addr, face_addr_len);
    }

    return res;
}
