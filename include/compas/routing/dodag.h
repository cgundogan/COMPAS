/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file dodag.h
 * @brief DODAG definitions for COMPAS
 * @author Cenk Gündoğan <mail-github@cgundogan.de>
 * @copyright GNU Lesser General Public License v2.1
 */

#ifndef COMPAS_ROUTING_DODAG_H
#define COMPAS_ROUTING_DODAG_H

#include <stdint.h>

/**
 * @brief Specify on compile time whether this node should be initialized as
 * DODAG root
 */
#ifndef COMPAS_RUN_AS_DODAG_ROOT
#define COMPAS_RUN_AS_DODAG_ROOT    (0)
#endif

/**
 * @brief Default rank when not part of a DODAG
 */
#define COMPAS_DODAG_UNDEF          (0)

/**
 * @brief Rank of the DODAG root
 */
#define COMPAS_DODAG_ROOT_RANK      (1)

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
 * @brief Immediate parent in the DODAG
 */
typedef struct {
    /** Face address of this parent (e.g. L2 address) */
    uint8_t face_addr[COMPAS_FACE_ADDR_LEN];
    uint8_t face_addr_len;      /**< Length of @ref face_addr */
} compas_parent_t;

/**
 * @brief DODAG definition
 */
typedef struct {
    uint16_t rank;              /**< Rank of the node */
    /** Default prefix of this DODAG */
    char prefix[COMPAS_PREFIX_LEN];
    uint16_t prefix_len;        /**< Length of @ref prefix */
    compas_parent_t parent;     /**< Immediate parent in the DODAG */
} compas_dodag_t;

/**
 * @brief Initialize DODAG root
 *
 * @param[in]   dodag           Pointer to the DODAG
 * @param[in]   prefix          Default prefix of the DODAG
 * @param[in]   prefix_len      Length of the prefix
 */
void compas_dodag_init_root(compas_dodag_t *dodag, const char *prefix,
                            uint16_t prefix_len);

/**
 * @brief Print DODAG to stdout
 * @note Requires @ref COMPAS_DEBUG @f$\neq 0@f$
 *
 * @param[in]   dodag           Pinter to the DODAG
 */
void compas_dodag_print(compas_dodag_t *dodag);

#endif /* COMPAS_ROUTING_DODAG_H */
