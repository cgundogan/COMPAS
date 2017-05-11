/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file nam.h
 * @brief Name Advertisement Message (NAM) definitions for COMPAS
 * @author Cenk Gündoğan <mail-github@cgundogan.de>
 * @copyright GNU Lesser General Public License v2.1
 */

#ifndef COMPAS_ROUTING_NAM_H
#define COMPAS_ROUTING_NAM_H

#include <stdbool.h>
#include <stdint.h>

#include "compas/compas.h"

/**
 * @brief NAM packet definition
 * @note @ref compas_tlv_t options may follow this struct immediately.
 */
typedef struct __attribute__((packed)) {
    uint8_t type;                   /**< Message type of a NAM */
    uint8_t len;                    /**< Total length of all options */
} compas_nam_t;

/**
 * @brief Create a NAM in @p nam
 *
 * @param[out]      nam             Pointer to the NAM
 */
void compas_nam_create(compas_nam_t *nam);

/**
 * @brief Add a TLV option with type @ref COMPAS_TLV_NAME to @p nam
 * @note Modifies compas_nam_t::len
 *
 * @param[in,out]   nam             Pointer to the NAM
 * @param[in]       name            Name to put into the NAM
 * @param[in]       name_len        Length of the name
 */
void compas_nam_tlv_add_name(compas_nam_t *nam, const char *name,
                             uint16_t name_len);

/**
 * @brief Add a TLV option with type @ref COMPAS_TLV_LIFETIME to @p nam
 * @note Modifies compas_nam_t::len
 *
 * @param[in,out]   nam             Pointer to the NAM
 * @param[in]       lifetime        Lifetime to put into the NAM
 */
void compas_nam_tlv_add_lifetime(compas_nam_t *nam, uint16_t lifetime);

/**
 * @brief Iterate over TLV options in @p nam
 *
 * @param[in]       nam             Pointer to the NAM
 * @param[in,out]   offset          Offset within the buffer; will be updated
 * @param[out]      tlv             Pointer to Current TLV
 *
 * @return          true, if more TLVs are available
 *                  false, if iterator is at the end
 */
bool compas_nam_tlv_iter(compas_nam_t *nam, uint16_t *offset,
                         compas_tlv_t **tlv);

#endif /* COMPAS_ROUTING_NAM_H */
