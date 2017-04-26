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

#include <stdbool.h>
#include <stdint.h>

#include "compas/compas.h"
#include "compas/seq.h"

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
 * @brief Flags for DODAGs
 */
typedef uint8_t compas_dodag_flags_t;

/**
 * @name DODAG flags
 * Flags for @ref compas_dodag_flags_t
 * @{
 */
/**
 * @brief En-/Disable floating DODAG
 */
#define COMPAS_DODAG_FLAGS_FLOATING (1 << 1)
/** @} */

/**
 * @name DODAG flags operations
 * Operatios on @ref compas_dodag_t::flags
 * @{
 */
/**
 * @brief Check whether DODAG is floating
 *
 * @param[in]   flags           @ref compas_dodag_flags_t
 *
 * @return      true, if @ref COMPAS_DODAG_FLAGS_FLOATING is set
 * @return      false, otherwise
 */
static inline bool compas_dodag_floating(compas_dodag_flags_t flags)
{
    return flags & COMPAS_DODAG_FLAGS_FLOATING;
}
/** @} */


/**
 * @brief Definition for DODAG parents
 */
typedef struct {
    /** Face address of this parent (e.g. L2 address) */
    uint8_t face_addr[COMPAS_FACE_ADDR_LEN];
    uint8_t face_addr_len;      /**< Length of compas_parent_t::face_addr */
} compas_parent_t;

/**
 * @brief DODAG definition
 */
typedef struct {
    compas_seq8_t freshness;    /**< Uplink freshness */
    uint8_t flags;              /**< DODAG flags */
    uint16_t rank;              /**< Rank of the node */
    char prefix[COMPAS_PREFIX_LEN]; /**< Default Prefix of this DODAG */
    uint16_t prefix_len;        /**< Length of compas_dodag_t::prefix */
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
 * @brief Compare @p face_addr with the current parent's address in @p dodag
 *
 * @param[in]   dodag           Pointer to the DODAG
 * @param[in]   face_addr       Address to check against
 * @param[in]   face_addr_len   Length of the address
 *
 * @return      true, if equal
 * @return      false, otherwise
 */
bool compas_dodag_parent_eq(compas_dodag_t *dodag, const uint8_t *face_addr,
                            uint8_t face_addr_len);

/**
 * @brief Print DODAG to stdout
 * @note Requires @ref COMPAS_DEBUG @f$\neq 0@f$
 *
 * @param[in]   dodag           Pinter to the DODAG
 */
void compas_dodag_print(compas_dodag_t *dodag);

#endif /* COMPAS_ROUTING_DODAG_H */
