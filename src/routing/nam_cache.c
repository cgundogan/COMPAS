/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <string.h>

#include "compas/routing/dodag.h"

compas_nam_cache_entry_t *compas_nam_cache_add(const compas_dodag_t *dodag,
                                               const compas_name_t *name,
                                               const compas_face_t *face)
{
    compas_nam_cache_entry_t *n, *new = NULL;

    unsigned i;
    for (i = 0; i < COMPAS_NAM_CACHE_LEN; ++i) {
        n = (compas_nam_cache_entry_t *) &dodag->nam_cache[i];

        if (!new && !n->in_use) {
            new = n;
        }

        if (!memcmp(&n->name, name, sizeof(n->name))) {
            break;
        }
    }

    if (new) {
        new->in_use = true;
        new->retries = COMPAS_NAM_CACHE_RETRIES;
        new->flags = 0;
        new->name = *name;
        if (face) {
            new->face = *face;
        }
        return new;
    }

    return NULL;
}

bool compas_nam_cache_del(const compas_dodag_t *dodag,
                          const compas_name_t *name)
{
    bool done = false;
    compas_nam_cache_entry_t *n;

    unsigned i;
    for (i = 0; i < COMPAS_NAM_CACHE_LEN; ++i) {
        n = (compas_nam_cache_entry_t *) &dodag->nam_cache[i];

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

compas_nam_cache_entry_t *compas_nam_cache_find(const compas_dodag_t *dodag,
                                                const compas_name_t *name)
{
    compas_nam_cache_entry_t *n, *found = NULL;

    unsigned i;
    for (i = 0; i < COMPAS_NAM_CACHE_LEN; ++i) {
        n = (compas_nam_cache_entry_t *) &dodag->nam_cache[i];

        if (n->in_use && (n->name.name_len == name->name_len)) {
            if (!memcmp(n->name.name, name->name, name->name_len)) {
                found = n;
                break;
            }
        }
    }


    return found;
}

bool compas_nam_cache_empty(const compas_dodag_t *dodag)
{
    unsigned i;
    for (i = 0; i < COMPAS_NAM_CACHE_LEN; ++i) {
        if(dodag->nam_cache[i].in_use) {
            return false;
        }
    }

    return true;
}
