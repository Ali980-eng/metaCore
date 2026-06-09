#pragma once
#ifndef TLIMITES_H
#define TLIMITES_H
#include <stdint.h>

/**
 * @file tlimites.h
 * @author ali lafi
 * @version 1.0
 * @date 2026-05-03
 */

#define MAX_VALUE_TIRT 1
#define MIN_VALUE_TIRT -1
#define MAX_VALUE_UTIRT 2
#define MIN_VALUE_UTIRT 0
#define MAX_VALUE_TYRT 364
#define MIN_VALUE_TYRT -364
#define MAX_VALUE_UTYRT 728
#define MIN_VALUE_UTYRT 0
#define MAX_VALUE_UB27 26
#define MIN_VALUE_UB27 0
#define MAX_VALUE_B27 13
#define MIN_VALUE_B27 -13


const uint8_t nullValue = 0;
// for Balanced Ternary Logic
const uint8_t true_b = 2;
const uint8_t unknown_b = 1;
const uint8_t false_b = -1;
// for Unbalanced Ternary Logic
const uint8_t true_u = 3;
const uint8_t unknown_u = 2;
const uint8_t false_u = 1;

#endif // TLIMITES_H