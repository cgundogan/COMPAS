/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file compas.h
 * @brief COMPAS specific definitions
 * @author Cenk Gündoğan <mail-github@cgundogan.de>
 * @copyright GNU Lesser General Public License v2.1
 */

#ifndef COMPAS_H
#define COMPAS_H

#include <stdint.h>

/**
 * @brief Max. length of a prefix
 */
#ifndef COMPAS_PREFIX_LEN
#define COMPAS_PREFIX_LEN           (32)
#endif

/**
 * @brief Max. length of a face address
 */
#ifndef COMPAS_FACE_ADDR_LEN
#define COMPAS_FACE_ADDR_LEN        (8)
#endif

/**
 * @name Message types
 * Each message is differentiated by a message type
 * @{
 */
/**
 * @brief Message type for PAM
 */
#define COMPAS_MSG_TYPE_PAM         (0xC0)

/**
 * @brief Message type for NAM
 */
#define COMPAS_MSG_TYPE_NAM         (0xC1)
/** @} */

/**
 * @name TLV options
 * @{
 */

/**
 * @brief TLV option for Names
 */
#define COMPAS_TLV_NAME             (0x00)

/**
 * @brief TLV option for Lifetimes
 */
#define COMPAS_TLV_LIFETIME         (0x01)

/** @} */

/**
 * @brief Type-Length-Value (TLV) option definition
 */
typedef struct __attribute__((packed)) {
    uint8_t type;               /**< Type of the TLV option */
    uint16_t length;            /**< Length of the TLV option */
} compas_tlv_t;

/**
 * @brief Add a new TLV option to the buffer
 *
 * @param[in]       buf             Buffer to write into
 * @param[in]       offset          Offset within the buffer to write into
 * @param[in]       type            TLV option type to write into the buffer
 * @param[in]       len             TLV option len to write into the buffer
 *
 * @return          Pointer to the newly added TLV @ref compas_tlv_t
 */
static inline compas_tlv_t *compas_tlv_add(uint8_t *buf, uint16_t offset,
                                           uint8_t type, uint16_t len)
{
    compas_tlv_t *tlv = (compas_tlv_t *) (buf + offset);
    tlv->type = type;
    tlv->length = len;
    return tlv;
}

/**
 * @brief Read an existing TLV option from the buffer
 *
 * @param[in]       buf             Buffer to read from
 * @param[in]       offset          Offset within the buffer
 *
 * @return          Buffer pointing to the start of the TLV option
 */
static inline compas_tlv_t *compas_tlv_read(uint8_t *buf, uint16_t offset)
{
    return (compas_tlv_t *) (buf + offset);
}

/**
 * @brief COMPAS messsage definition
 */
typedef struct __attribute__((packed)) {
    uint8_t type;               /**< Message type of a compas messsage */
} compas_message_t;

#endif /* COMPAS_H */
