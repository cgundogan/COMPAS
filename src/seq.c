/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include "compas/seq.h"

compas_seq8_t compas_seq8_add(compas_seq8_t s, uint8_t n)
{
    if (n > (UINT8_MAX >> 1)) {
        return s;
    }

    return (s + n);
}

int compas_seq8_cmp(compas_seq8_t s1, compas_seq8_t s2)
{
    if (s1 == s2) {
        return 0;
    }

    if (((s1 < s2) && ((uint8_t)(s2 - s1) < ((UINT8_MAX >> 1) + 1))) ||
            ((s1 > s2) && ((uint8_t)(s1 - s2) > ((UINT8_MAX >> 1) + 1)))) {
        return -1;
    }

    if (((s1 < s2) && ((uint8_t)(s2 - s1) > ((UINT8_MAX >> 1) + 1))) ||
            ((s1 > s2) && ((uint8_t)(s1 - s2) < ((UINT8_MAX >> 1) + 1)))) {
        return 1;
    }

    return -EINVAL;
}
