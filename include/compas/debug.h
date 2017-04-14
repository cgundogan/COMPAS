/*
 * Copyright (C) 2017 HAW Hamburg
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @file debug.h
 * @brief Debugging specific definitions
 * @author Cenk Gündoğan <mail-github@cgundogan.de>
 * @copyright GNU Lesser General Public License v2.1
 */

#ifndef COMPAS_DEBUG_H
#define COMPAS_DEBUG_H

#include <stdio.h>

/**
 * Control debug printing
 */
#ifndef COMPAS_DEBUG
#define COMPAS_DEBUG 0
#endif

/**
 * Print debug messages if COMPAS_DEBUG is not 0
 */
#define CDBG_PRINT(...) do { if (COMPAS_DEBUG) printf(__VA_ARGS__); } while (0)

#endif /* COMPAS_DEBUG_H */
