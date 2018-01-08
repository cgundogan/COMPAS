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
#include <string.h>

/**
 * @addtogroup configurables
 * These options are cofigurable via CFLAGS on compile time
 * @{
 */
/**
 * @brief Max. length of a prefix
 */
#ifndef COMPAS_PREFIX_LEN
#define COMPAS_PREFIX_LEN           (32)
#endif

/**
 * @brief Max. length of a name suffix
 */
#ifndef COMPAS_NAME_SUFFIX_LEN
#define COMPAS_NAME_SUFFIX_LEN      (32)
#endif

/**
 * @brief Max. length of a face address
 */
#ifndef COMPAS_FACE_ADDR_LEN
#define COMPAS_FACE_ADDR_LEN        (8)
#endif
/** @} */

/**
 * @brief Max. length of a name
 */
#define COMPAS_NAME_LEN             (COMPAS_PREFIX_LEN + COMPAS_NAME_SUFFIX_LEN)

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
 * @brief Message type for SOL
 */
#define COMPAS_MSG_TYPE_SOL         (0xC2)
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

/**
 * @brief TLV option for Name ACKs
 */
#define COMPAS_TLV_NAME_ACK         (0x02)

/** @} */

/**
 * @brief Face (L2 address)
 */
typedef struct {
    /** Face address of this parent (e.g. L2 address) */
    uint8_t face_addr[COMPAS_FACE_ADDR_LEN];
    uint8_t face_addr_len;      /**< Length of compas_parent_t::face_addr */
} compas_face_t;

/**
 * @brief Initialize a compas_face_t
 *
 * @param[out]      face            Face to initializ
 * @param[in]       face_addr       Face address
 * @param[in]       face_addr_len   Length of face address
 */
static inline void compas_face_init(compas_face_t *face,
                                    const uint8_t *face_addr,
                                    uint8_t face_addr_len)
{
    face->face_addr_len = face_addr_len;
    memcpy(face->face_addr, face_addr,
           (face_addr_len > COMPAS_FACE_ADDR_LEN) ?
           COMPAS_FACE_ADDR_LEN : face_addr_len);
}

/**
 * @brief Prefix representation
 */
typedef struct {
    /**< Prefix */
    char prefix[COMPAS_PREFIX_LEN];
    uint16_t prefix_len;            /**< Length of a prefix */
} compas_prefix_t;

/**
 * @brief Initialize a compas_prefix_t
 *
 * @param[out]      prefix          Prefix to initializ
 * @param[in]       p               Prefix
 * @param[in]       p_len           Length of prefix
 */
static inline void compas_prefix_init(compas_prefix_t *prefix,
                                      const char *p, uint16_t p_len)
{
    prefix->prefix_len = p_len;
    memcpy(prefix->prefix, p,
           (p_len > COMPAS_PREFIX_LEN) ? COMPAS_PREFIX_LEN : p_len);
}

/**
 * @brief Name representation
 */
typedef struct {
    char name[COMPAS_NAME_LEN]; /**< Name */
    uint16_t name_len;          /**< Length of a name */
} compas_name_t;

/**
 * @brief Initialize a compas_name_t
 *
 * @param[out]      name            Name to initializ
 * @param[in]       n               Name
 * @param[in]       n_len           Length of name
 */
static inline void compas_name_init(compas_name_t *name,
                                    const char *n, uint16_t n_len)
{
    name->name_len = n_len;
    memcpy(name->name, n,
           (n_len > COMPAS_NAME_LEN) ? COMPAS_NAME_LEN : n_len);
}

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
 * @param[out]      buf             Buffer to write into
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
