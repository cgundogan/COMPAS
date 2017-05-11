/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <string.h>

#include "compas/routing/dodag.h"

bool compas_nam_cache_add(compas_dodag_t *dodag, const compas_name_t *name,
                          const compas_face_t *face)
{
    bool done = false;
    compas_nam_cache_entry_t *n, *new = NULL;

    for (unsigned i=0; i < COMPAS_DODAG_NAM_CACHE_LEN; ++i) {
        n = &dodag->nam_cache[i];

        if (!new && !n->in_use) {
            new = n;
        }

        if (!memcmp(&n->name, name, sizeof(n->name))) {
            break;
        }
    }

    if (new && !done) {
        new->in_use = true;
        new->name = *name;
        if (face) {
            new->face = *face;
        }
        done = true;
    }

    return done;
}

bool compas_nam_cache_del(compas_dodag_t *dodag, const compas_name_t *name)
{
    bool done = false;
    compas_nam_cache_entry_t *n;

    for (unsigned i = 0; i < COMPAS_DODAG_NAM_CACHE_LEN; ++i) {
        n = &dodag->nam_cache[i];

        if (n->in_use && !memcmp(n->name.name, name->name,
                                 (n->name.name_len < name->name_len) ?
                                  n->name.name_len : name->name_len)) {
            memset(n, 0, sizeof(*n));
            done = true;
            break;
        }
    }


    return done;
}

compas_nam_cache_entry_t *compas_nam_cache_find(compas_dodag_t *dodag,
                                                const compas_name_t *name)
{
    compas_nam_cache_entry_t *n, *found = NULL;

    for (unsigned i = 0; i < COMPAS_DODAG_NAM_CACHE_LEN; ++i) {
        n = &dodag->nam_cache[i];

        if (n->in_use && !memcmp(n->name.name, name->name,
                                 (n->name.name_len < name->name_len) ?
                                  n->name.name_len : name->name_len)) {
            found = n;
            break;
        }
    }


    return found;
}

bool compas_nam_cache_empty(compas_dodag_t *dodag)
{
    for (unsigned i = 0; i < COMPAS_DODAG_NAM_CACHE_LEN; ++i) {
        if(dodag->nam_cache[i].in_use) {
            return false;
        }
    }

    return true;
}
