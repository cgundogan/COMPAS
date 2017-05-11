/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file pam.h
 * @brief Prefix Advertisement Message (PAM) definitions for COMPAS
 * @author Cenk Gündoğan <mail-github@cgundogan.de>
 * @copyright GNU Lesser General Public License v2.1
 */

#ifndef COMPAS_ROUTING_PAM_H
#define COMPAS_ROUTING_PAM_H

#include <stdint.h>

#include "compas/seq.h"
#include "compas/routing/dodag.h"

/**
 * @brief PAM packet definition
 * @note The name prefix follows this struct immediately and is of length
 * compas_pam_t::prefix_len.
 */
typedef struct __attribute__((packed)) {
    uint8_t type;               /**< Message type of a PAM */
    compas_dodag_flags_t flags; /**< DODAG flags @ref compas_dodag_flags_t */
    compas_seq8_t freshness;    /**< Uplink freshness */
    uint16_t rank;              /**< Rank of the sender */
    uint16_t prefix_len;        /**< Length of the prefix */
} compas_pam_t;

/**
 * @defgroup compas_pam_ret_codes PAM parsing return codes
 * Return codes for compas_pam_check()
 * @{
 */
/**
 * @brief Code for current parent after PAM parsing
 */
#define COMPAS_PAM_RET_CODE_CURRPARENT      (0)
/**
 * @brief Code for new parent after PAM parsing
 */
#define COMPAS_PAM_RET_CODE_NEWPARENT       (1)
/**
 * @brief Code for ROOT rank
 */
#define COMPAS_PAM_RET_CODE_ROOTRANK        (2)
/**
 * @brief Code for MAX rank
 */
#define COMPAS_PAM_RET_CODE_MAXRANK         (3)
/**
 * @brief Code for outdated DODAG
 */
#define COMPAS_PAM_RET_CODE_OLDDODAG        (4)
/**
 * @brief Code for PAM with worse rank
 */
#define COMPAS_PAM_RET_CODE_WORSERANK       (5)
/**
 * @brief Code for PAM with floating DODAG
 */
#define COMPAS_PAM_RET_CODE_FLOATINGDODAG   (6)
/** @} */

/**
 * @brief Check validity of PAM @p pam
 *
 * @param[out]  dodag           Pointer to the DODAG
 * @param[in]   pam             Pointer to PAM to parse from
 * @param[in]   face            Pointer to the face
 *
 * @return      @ref compas_pam_ret_codes
 */
int compas_pam_check(const compas_dodag_t *dodag, const compas_pam_t *pam,
                     const compas_face_t *face);

/**
 * @brief Create a PAM in @p pam
 *
 * @param[in]   dodag           Pointer to the DODAG
 * @param[out]  pam             Pointer to the PAM to fill
 */
void compas_pam_create(const compas_dodag_t *dodag, compas_pam_t *pam);

/**
 * @brief Get length needed for a PAM
 *
 * @param[in]   dodag           Pointer to the DODAG
 *
 * @return      The length of the PAM to be created
 */
size_t compas_pam_len(const compas_dodag_t *dodag);

/**
 * @brief Parse PAM @p pam into DODAG @p dodag
 *
 * If @f$pam_{rank} >= dodag_{rank}@f$, then @p pam will not be parsed.
 *
 * @param[out]  dodag           Pointer to the DODAG
 * @param[in]   pam             Pointer to PAM to parse from
 * @param[in]   face_addr       Face address (e.g. L2 address)
 * @param[in]   face_addr_len   Length of face address @p face_addr
 *
 * @return      0, on parsing PAM from currently selected parent
 * @return      1, on parsing PAM from new parent
 * @return      < 0, on failure
 */
int compas_pam_parse(compas_dodag_t *dodag, const compas_pam_t *pam,
                     const uint8_t *face_addr, uint8_t face_addr_len);

#endif /* COMPAS_ROUTING_PAM_H */
