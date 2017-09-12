/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file trickle.h
 * @brief Trickle Algorithm (RFC 6206)
 * @author Cenk Gündoğan <cenk.guendogan@haw-hamburg.de>
 * @copyright GNU Lesser General Public License v2.1
 */

#ifndef COMPAS_TRICKLE_H
#define COMPAS_TRICKLE_H

#include <stdint.h>
#include <errno.h>

/**
 * @brief Trickle timer definition
 */
typedef struct {
    uint8_t k;                      /**< redundancy constant */

    /**
     * @brief maximum interval size, described as doublings
     */
    uint8_t Imax;

    uint16_t c;                     /**< counter */
    uint32_t Imin;                  /**< minimum interval size */
    uint32_t I;                     /**< current interval size */
    uint32_t t;                     /**< time within the current interval */
} trickle_t;

/**
 * @brief increments the counter by one
 *
 * @param[in] trickle   trickle timer
 */
void trickle_increment_counter(trickle_t *trickle);

/**
 * @brief initialize the Trickle timer
 *
 * @pre `Imin > 0`
 * @pre `(Imin << Imax) < (UINT32_MAX / 2)` to avoid overflow of uint32_t
 *
 * @param[in] trickle               trickle timer
 * @param[in] Imin                  minimum interval
 * @param[in] Imax                  maximum interval
 * @param[in] k                     redundancy constant
 */
void trickle_init(trickle_t *trickle, uint32_t Imin, uint8_t Imax, uint8_t k);

/**
 * @brief calculate the next interval
 *
 * @pre `(trickle->I > 0)` required for trickle algorithm to work
 *
 * @param[in] trickle   trickle timer
 *
 * @return  next interval in ms.
 */
uint64_t trickle_next(trickle_t *trickle);

#endif /* COMPAS_TRICKLE_H */
