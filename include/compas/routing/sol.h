/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file sol.h
 * @brief Solicitation (SOL) definitions for COMPAS
 * @author Cenk Gündoğan <mail-github@cgundogan.de>
 * @copyright GNU Lesser General Public License v2.1
 */

#ifndef COMPAS_ROUTING_SOL_H
#define COMPAS_ROUTING_SOL_H

#include <stdbool.h>
#include <stdint.h>
#include <compas/compas.h>

/**
 * @brief Flags for compas_sol_t::flags
 */
typedef uint8_t compas_sol_flags_t;

/**
 * @brief SOL packet definition
 */
typedef struct __attribute__((packed)) {
    uint8_t type;               /**< Message type of a SOL */
    compas_sol_flags_t flags;   /**< SOL flags */
} compas_sol_t;

/**
 * @name SOL flags
 * Flags for @ref compas_sol_t::flags
 * @{
 */
/**
 * @brief Reset Trickle if set
 */
#define COMPAS_SOL_FLAGS_TRICKLE    (1 << 0)

/**
 * @brief Check whether Trickle flag is set
 *
 * @param[in]   flags           @ref compas_sol_flags_t
 *
 * @return      true, if @ref COMPAS_SOL_FLAGS_TRICKLE is set
 * @return      false, otherwise
 */
static inline bool compas_sol_reset_trickle(compas_sol_flags_t flags)
{
    return flags & COMPAS_SOL_FLAGS_TRICKLE;
}
/** @} */

/**
 * @brief Create a SOL in @p sol
 *
 * @param[out]  sol             Pointer to the SOL to fill
 * @param[in]   sol             Flags for the SOL
 */
void compas_sol_create(compas_sol_t *sol, uint8_t flags);

/**
 * @brief Get length needed for a SOL
 *
 * @return      The length of the SOL to be created
 */
size_t compas_sol_len(void);

/**
 * @brief Parse SOL @p sol
 *
 * @param[in]   sol             Pointer to PAM to parse from
 */
void compas_sol_parse(const compas_sol_t *sol);

#endif /* COMPAS_ROUTING_SOL_H */
