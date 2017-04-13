/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "compas/routing/pam.h"

void compas_pam_set_prefix(compas_dodag_t *dodag, compas_pam_t *pam)
{
    pam->prefix_len = dodag->prefix_len;
    memcpy(pam + 1, dodag->prefix, dodag->prefix_len);
}

void compas_pam_create(compas_dodag_t *dodag, compas_pam_t *pam)
{
	compas_pam_set_prefix(dodag, pam);
}
