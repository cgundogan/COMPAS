/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <stdlib.h>
#include "assert.h"
#include "compas/trickle.h"

void trickle_increment_counter(trickle_t *trickle)
{
    trickle->c++;
}

void trickle_init(trickle_t *trickle, uint32_t Imin, uint8_t Imax, uint8_t k)
{
    assert(Imin > 0);
    assert((Imin << Imax) < (UINT32_MAX / 2));

    trickle->c = 0;
    trickle->k = k;
    trickle->Imin = Imin;
    trickle->Imax = Imax;
    trickle->I = trickle->t = COMPAS_TRICKLE_RAND_RANGE(trickle->Imin, 4 * trickle->Imin);
}

uint64_t trickle_next(trickle_t *trickle)
{
    assert(trickle->I > 0);

    uint32_t old_interval = trickle->I;
    uint32_t max_interval = trickle->Imin << trickle->Imax;
    uint32_t diff = old_interval - trickle->t;

    trickle->I *= 2;
    if (trickle->I > max_interval) {
        trickle->I = max_interval;
        old_interval = max_interval / 2;
    }

    trickle->c = 0;
    /* old_interval == trickle->I / 2 */
    trickle->t = COMPAS_TRICKLE_RAND_RANGE(old_interval, trickle->I);

    return (trickle->t + diff);
}
