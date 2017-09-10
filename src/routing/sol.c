/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <string.h>

#include "compas/debug.h"
#include "compas/routing/sol.h"

void compas_sol_create(compas_sol_t *sol)
{
    sol->type = COMPAS_MSG_TYPE_SOL;
}

size_t compas_sol_len(void)
{
    return sizeof(compas_sol_t);
}

void compas_sol_parse(const compas_sol_t *sol)
{
    (void) sol;
    return;
}
