/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "routing/pam.h"

void routing_pam_set_prefix(routing_pam_t *pam, const char *prefix,
                            uint16_t prefix_len)
{
    pam->prefix_len = prefix_len;
    memcpy(pam + 1, prefix, prefix_len);
}
