/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "compas/routing/nam.h"

void compas_nam_set_name(compas_nam_t *nam, const char *name,
                         uint16_t name_len)
{
    nam->name_len = name_len;
    memcpy(nam + 1, name, name_len);
}
