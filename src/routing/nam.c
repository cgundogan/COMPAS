/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#include <string.h>

#include "compas/compas.h"
#include "compas/routing/nam.h"

void compas_nam_create(compas_nam_t *nam)
{
    nam->type = COMPAS_MSG_TYPE_NAM;
    nam->len = 0;
}

void compas_nam_tlv_add_name(compas_nam_t *nam, const compas_name_t *name)
{
    compas_tlv_t *tlv = compas_tlv_add((uint8_t *) (nam + 1), nam->len,
                                  COMPAS_TLV_NAME, name->name_len);
    memcpy((uint8_t *)(tlv + 1), name->name, name->name_len);
    nam->len += tlv->length + sizeof(compas_tlv_t);
}

void compas_nam_tlv_add_name_ack(compas_nam_t *nam, const compas_name_t *name)
{
    compas_tlv_t *tlv = compas_tlv_add((uint8_t *) (nam + 1), nam->len,
                                  COMPAS_TLV_NAME_ACK, name->name_len);
    memcpy((uint8_t *)(tlv + 1), name->name, name->name_len);
    nam->len += tlv->length + sizeof(compas_tlv_t);
}

void compas_nam_tlv_add_lifetime(compas_nam_t *nam, uint16_t lifetime)
{
    compas_tlv_t *tlv = compas_tlv_add((uint8_t *) (nam + 1), nam->len,
                                  COMPAS_TLV_LIFETIME, sizeof(lifetime));
    memcpy((uint8_t *)(tlv + 1), &lifetime, sizeof(lifetime));
    nam->len += tlv->length + sizeof(compas_tlv_t);
}

bool compas_nam_tlv_iter(compas_nam_t *nam, uint16_t *offset,
                         compas_tlv_t **tlv)
{
    if (nam->len - *offset == 0) {
        return false;
    }

    *tlv = compas_tlv_read((uint8_t *) (nam + 1), *offset);
    *offset += (*tlv)->length + sizeof(compas_tlv_t);

    return true;
}
