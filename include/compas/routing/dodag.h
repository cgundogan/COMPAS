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
 * @addtogroup configurables
 * @{
 */
/**
 * @brief Specify on compile time whether this node should be initialized as
 * DODAG root
 */
#ifndef COMPAS_RUN_AS_DODAG_ROOT
#define COMPAS_RUN_AS_DODAG_ROOT    (0)
#endif
/** @} */

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
#define COMPAS_DODAG_FLAGS_FLOATING (1 << 0)

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
 * @addtogroup configurables
 * @{
 */
/**
 * @brief Length of the nam cache
 */
#ifndef COMPAS_DODAG_NAM_CACHE_LEN
#define COMPAS_DODAG_NAM_CACHE_LEN (8U)
#endif
/** @} */

/**
 * @brief Flags for NAM Cache
 */
typedef uint8_t compas_nam_cache_flags_t;

/**
 * @name NAM Cache flags
 * Flags for @ref compas_nam_cache_flags_t
 * @{
 */
/**
 * @brief Set, if content originates from here
 */
#define COMPAS_NAM_CACHE_FLAGS_ORIGINATES   (1 << 0)

/**
 * @brief Check whether content originates from here
 *
 * @param[in]   flags           @ref compas_nam_cache_flags_t
 *
 * @return      true, if @ref COMPAS_NAM_CACHE_FLAGS_ORIGINATES is set
 * @return      false, otherwise
 */
static inline bool compas_nam_cache_originates(compas_nam_cache_flags_t flags)
{
    return flags & COMPAS_NAM_CACHE_FLAGS_ORIGINATES;
}
/** @} */

/**
 * @brief NAM cache
 */
typedef struct compas_nam_cache_entry {
    bool in_use;                    /**< State of this entry */
    bool flags;                     /**< Flags for a nam cache entry */
    compas_name_t name;             /**< Name to request Data with */
    compas_face_t face;             /**< Incoming face of NAM */
} compas_nam_cache_entry_t;

/**
 * @brief Definition for DODAG parents
 */
typedef struct {
    compas_face_t face;         /**< face to this parent */
} compas_parent_t;

/**
 * @brief DODAG definition
 */
typedef struct {
    compas_seq8_t freshness;    /**< Uplink freshness */
    uint8_t flags;              /**< DODAG flags */
    uint16_t rank;              /**< Rank of the node */
    compas_prefix_t prefix;     /**< Default Prefix of this DODAG */
    compas_parent_t parent;     /**< Immediate parent in the DODAG */
                                /**< NAM cache */
    compas_nam_cache_entry_t nam_cache[COMPAS_DODAG_NAM_CACHE_LEN];
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
 * @param[in]   face            Face to check against
 *
 * @return      true, if equal
 * @return      false, otherwise
 */
bool compas_dodag_parent_eq(const compas_dodag_t *dodag,
                            const compas_face_t *face);

/**
 * @brief Print DODAG to stdout
 * @note Requires @ref COMPAS_DEBUG @f$\neq 0@f$
 *
 * @param[in]   dodag           Pinter to the DODAG
 */
void compas_dodag_print(compas_dodag_t *dodag);

/**
 * @brief Add a new entry into the nam cache in @p dodag
 *
 * @param[in]   dodag           Pointer to the DODAG
 * @param[in]   name            Name to store
 * @param[in]   face            Face to store
 *
 * @return      true, if successful
 * @return      false, if no space left in nam cache
 */
bool compas_nam_cache_add(compas_dodag_t *dodag, const compas_name_t *name,
                          const compas_face_t *face);

/**
 * @brief Delete an existing entry from the nam cache in @p dodag
 *
 * @param[in]   dodag           Pointer to the DODAG
 * @param[in]   name            Name to delete
 *
 * @return      true, if successful
 * @return      false, if no entry with @p name is found
 */
bool compas_nam_cache_del(compas_dodag_t *dodag, const compas_name_t *name);

/**
 * @brief Finds an existing entry from the nam cache in @p dodag
 *
 * @param[in]   dodag           Pointer to the DODAG
 * @param[in]   name            Name to delete
 *
 * @return      Pointer to the entry, if present
 * @return      NULL, if not present
 */
compas_nam_cache_entry_t *compas_nam_cache_find(compas_dodag_t *dodag,
                                                const compas_name_t *name);
/**
 * @brief Checks whether the NAM cache for @p dodag is empty
 *
 * @param[in]   dodag           Pointer to the DODAG
 *
 * @return      true, if NAM cache is empty
 * @return      false, otherwise
 */
bool compas_nam_cache_empty(compas_dodag_t *dodag);

#endif /* COMPAS_ROUTING_DODAG_H */
