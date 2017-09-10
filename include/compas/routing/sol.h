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

#include <stdint.h>
#include <compas/compas.h>

/**
 * @brief SOL packet definition
 */
typedef struct __attribute__((packed)) {
    uint8_t type;               /**< Message type of a SOL */
} compas_sol_t;

/**
 * @brief Create a SOL in @p sol
 *
 * @param[out]  sol             Pointer to the SOL to fill
 */
void compas_sol_create(compas_sol_t *sol);

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
