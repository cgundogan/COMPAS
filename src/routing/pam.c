/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "compas/routing/pam.h"

void compas_pam_create(compas_dodag_t *dodag, compas_pam_t *pam)
{
    pam->rank = dodag->rank;
    pam->prefix_len = dodag->prefix_len;
    memcpy(pam + 1, dodag->prefix, dodag->prefix_len);
}

size_t compas_pam_len(compas_dodag_t *dodag)
{
    size_t len = 0;
    len  += sizeof(compas_pam_t);
    len  += dodag->prefix_len;
    return len;
}
