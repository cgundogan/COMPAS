/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "compas/routing/dodag.h"
#include "compas/routing/nam.h"

void compas_nam_create(const char *name, uint16_t name_len, compas_nam_t *nam)
{
    nam->type = COMPAS_MSG_TYPE_NAM;
    nam->name_len = (name_len < COMPAS_NAME_LEN) ? name_len : COMPAS_NAME_LEN;
    memcpy(nam + 1, name, nam->name_len);
}

void compas_nam_parse(char *name, uint16_t *name_len, const compas_nam_t *nam)
{
    uint16_t len = (nam->name_len < COMPAS_NAME_LEN) ?
                    nam->name_len : COMPAS_NAME_LEN;
    *name_len = len;
    memcpy(name, nam + 1, len);

}
