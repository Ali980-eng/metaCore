#include "cgen/bitUtilitys.h"
#include "cgen/micros.h"

/**
 * @file bitUtilitys.c
 * @brief Comprehensive test suite for bitUtilitys library
 * @details Tests all bit manipulation operations:
 *          - get_*bit() - retrieve bit values
 *          - set_*bit() - set bits to 1
 *          - reset_*bit() - clear bits to 0
 *          - toggle_*bit() - flip bit values
 *          - xchg_*bit() - exchange/swap bits
 *          - count_*bit() - count set/unset bits
 *          Covers uint8, int8, uint16, int16, uint32, int32, uint64, int64
 */

MAIN_TEST(bitUtilitys);

  // ==================== 8-BIT UNSIGNED INTEGER TESTS ====================
  // Testing: get_u8bit, set_u8bit, reset_u8bit, toggle_u8bit, xchg_u8bit, count_u8bit
  
  uint8_t value_1 = 8;                     // value_1: 0000-1000
  TEST_2(get_u8bit(value_1, 0), false);     // bit 0 should be 0
  TEST_2(get_u8bit(value_1, 3), true);      // bit 3 should be 1
  TEST_2(get_u8bit(value_1, 7), false);     // bit 7 should be 0
  
  value_1 = set_u8bit(value_1, 0);         // value_1: 0000-1001
  TEST_2(get_u8bit(value_1, 0), true);      // bit 0 should now be 1
  
  value_1 = set_u8bit(value_1, 7);         // value_1: 1000-1001
  TEST_2(get_u8bit(value_1, 7), true);      // bit 7 should now be 1
  
  uint8_t value_2 = 99;                    // value_2: 0110-0011
  TEST_2(get_u8bit(value_2, 6), true);      // bit 6 should be 1
  
  value_2 = reset_u8bit(value_2, 6);       // value_2: 0010-0011
  TEST_2(get_u8bit(value_2, 6), false);     // bit 6 should be cleared
  
  value_2 = set_u8bit(value_2, 7);         // value_2: 1010-0011
  TEST_2(get_u8bit(value_2, 7), true);      // bit 7 should be set
  
  value_2 = set_u8bit(value_2, 3);         // value_2: 1010-1011
  TEST_2(get_u8bit(value_2, 3), true);      // bit 3 should be set
  
  value_2 = reset_u8bit(value_2, 1);       // value_2: 1010-1001
  TEST_2(get_u8bit(value_2, 1), false);     // bit 1 should be cleared

  uint8_t value_3 = 16;                    // value_3: 0001-0000
  TEST_2(get_u8bit(value_3, 0), false);     // bit 0 should be 0
  TEST_2(get_u8bit(value_3, 4), true);      // bit 4 should be 1
  
  value_3 = xchg_u8bit(value_3, 4, 0);     // value_3: 0000-0001, exchange bits 4 and 0
  TEST_2(get_u8bit(value_3, 0), true);      // bit 0 should be 1
  TEST_2(get_u8bit(value_3, 4), false);     // bit 4 should be 0
  
  value_3 = reset_u8bit(value_3, 0);       // value_3: 0000-0000
  TEST_2(value_3, 0);                       // value should be 0

  uint8_t value_4 = 35;                    // value_4: 0010-0011
  TEST_2(get_u8bit(value_4, 0), true);      // bit 0 should be 1
  TEST_2(get_u8bit(value_4, 7), false);     // bit 7 should be 0
  
  value_4 = toggle_u8bit(value_4, 0);      // value_4: 0010-0010, toggle bit 0
  TEST_2(get_u8bit(value_4, 0), false);     // bit 0 should be 0
  
  value_4 = toggle_u8bit(value_4, 7);      // value_4: 1010-0010, toggle bit 7
  TEST_2(get_u8bit(value_4, 7), true);      // bit 7 should be 1
  
  value_4 = xchg_u8bit(value_4, 5, 0);     // value_4: 1000-0011
  TEST_2(get_u8bit(value_4, 5), false);     // bit 5 should be 0

  // Test count_u8bit for various patterns
  TEST_2(count_u8bit(value_1, true), 3);    // value_1 has 3 set bits
  TEST_2(count_u8bit(value_2, true), 4);    // value_2 has 4 set bits
  TEST_2(count_u8bit(value_3, true), 0);    // value_3 has 0 set bits
  TEST_2(count_u8bit(value_3, false), 8);   // value_3 has 8 unset bits
  TEST_2(count_u8bit(value_4, false), 5);   // value_4 has 5 unset bits

  // ==================== 8-BIT SIGNED INTEGER TESTS ====================
  // Testing: get_8bit, set_8bit, reset_8bit, toggle_8bit, xchg_8bit, count_8bit
  
  int8_t value_5 = -2;                     // value_5: 1111-1110 (two's complement)
  TEST_2(get_8bit(value_5, 0), false);      // bit 0 should be 0
  
  value_5 = set_8bit(value_5, 0);
  TEST_2(get_8bit(value_5, 0), true);       // bit 0 should be 1
  TEST_2(get_8bit(value_5, 5), true);       // bit 5 should be 1
  
  value_5 = toggle_8bit(value_5, 5);
  TEST_2(get_8bit(value_5, 5), false);      // bit 5 should be toggled to 0
  TEST_2(count_8bit(value_5, true), 7);     // should have 7 set bits

  int8_t value_6 = 88;                     // value_6: 0101-1000
  TEST_2(get_8bit(value_6, 3), true);       // bit 3 should be 1
  TEST_2(get_8bit(value_6, 4), true);       // bit 4 should be 1
  
  value_6 = xchg_8bit(value_6, 3, 1);      // exchange bits 3 and 1
  TEST_2(get_8bit(value_6, 1), true);       // bit 1 should be 1
  TEST_2(get_8bit(value_6, 3), false);      // bit 3 should be 0
  
  value_6 = toggle_8bit(value_6, 4);
  TEST_2(get_8bit(value_6, 4), false);      // bit 4 should be toggled to 0
  
  value_6 = reset_8bit(value_6, 1);
  TEST_2(get_8bit(value_6, 1), false);      // bit 1 should be 0

  // ==================== 16-BIT UNSIGNED INTEGER TESTS ====================
  // Testing: get_u16bit, set_u16bit, reset_u16bit, toggle_u16bit, xchg_u16bit, count_u16bit
  
  uint16_t value_7 = 3380;                 // Binary: 1101001110100
  TEST_2(get_u16bit(value_7, 7), false);    // bit 7 should be 0
  TEST_2(get_u16bit(value_7, 8), true);     // bit 8 should be 1
  
  value_7 = toggle_u16bit(value_7, 7);
  TEST_2(get_u16bit(value_7, 7), true);     // bit 7 should be toggled to 1
  
  value_7 = reset_u16bit(value_7, 8);
  TEST_2(get_u16bit(value_7, 8), false);    // bit 8 should be 0
  TEST_2(get_u16bit(value_7, 1), false);    // bit 1 should be 0
  
  value_7 = set_u16bit(value_7, 1);
  TEST_2(get_u16bit(value_7, 1), true);     // bit 1 should be set

  uint16_t value_8 = 255;                  // Binary: 0000000011111111
  TEST_2(count_u16bit(value_8, true), 8);   // should have 8 set bits
  TEST_2(count_u16bit(value_8, false), 8);  // should have 8 unset bits
  
  value_8 = set_u16bit(value_8, 15);
  TEST_2(get_u16bit(value_8, 15), true);    // MSB should be set
  TEST_2(count_u16bit(value_8, true), 9);   // should have 9 set bits

  uint16_t value_9 = 1024;                 // Binary: 0000010000000000, bit 10 is set
  TEST_2(get_u16bit(value_9, 10), true);    // bit 10 should be 1
  TEST_2(get_u16bit(value_9, 0), false);    // bit 0 should be 0
  
  value_9 = xchg_u16bit(value_9, 10, 0);   // exchange bits 10 and 0
  TEST_2(get_u16bit(value_9, 0), true);     // bit 0 should be 1
  TEST_2(get_u16bit(value_9, 10), false);   // bit 10 should be 0

  // ==================== 16-BIT SIGNED INTEGER TESTS ====================
  // Testing: get_16bit, set_16bit, reset_16bit, toggle_16bit, xchg_16bit, count_16bit
  
  int16_t value_10 = 256;                  // Binary: 0000000100000000, bit 8 is set
  TEST_2(get_16bit(value_10, 8), true);     // bit 8 should be 1
  TEST_2(get_16bit(value_10, 9), false);    // bit 9 should be 0
  
  value_10 = set_16bit(value_10, 9);
  TEST_2(get_16bit(value_10, 9), true);     // bit 9 should be set
  
  value_10 = toggle_16bit(value_10, 8);
  TEST_2(get_16bit(value_10, 8), false);    // bit 8 should be toggled to 0
  TEST_2(count_16bit(value_10, true), 1);   // should have 1 set bit

  // ==================== 32-BIT UNSIGNED INTEGER TESTS ====================
  // Testing: get_u32bit, set_u32bit, reset_u32bit, toggle_u32bit, xchg_u32bit, count_u32bit
  
  uint32_t value_11 = 65536;               // Binary: bit 16 is set
  TEST_2(get_u32bit(value_11, 16), true);   // bit 16 should be 1
  TEST_2(get_u32bit(value_11, 0), false);   // bit 0 should be 0
  
  value_11 = set_u32bit(value_11, 0);
  TEST_2(get_u32bit(value_11, 0), true);    // bit 0 should be set
  
  value_11 = reset_u32bit(value_11, 16);
  TEST_2(get_u32bit(value_11, 16), false);  // bit 16 should be cleared
  TEST_2(count_u32bit(value_11, true), 1);  // should have 1 set bit

  uint32_t value_12 = 0xFFFF;              // All lower 16 bits set
  TEST_2(count_u32bit(value_12, true), 16); // should have 16 set bits
  
  value_12 = toggle_u32bit(value_12, 31);  // toggle MSB
  TEST_2(get_u32bit(value_12, 31), true);   // MSB should be set
  TEST_2(count_u32bit(value_12, true), 17); // should have 17 set bits

  uint32_t value_13 = 0x80000000;          // Only MSB is set
  TEST_2(get_u32bit(value_13, 31), true);   // bit 31 should be 1
  
  value_13 = xchg_u32bit(value_13, 31, 0); // exchange MSB and LSB
  TEST_2(get_u32bit(value_13, 0), true);    // bit 0 should be 1
  TEST_2(get_u32bit(value_13, 31), false);  // bit 31 should be 0

  // ==================== 32-BIT SIGNED INTEGER TESTS ====================
  // Testing: get_32bit, set_32bit, reset_32bit, toggle_32bit, xchg_32bit, count_32bit
  
  int32_t value_14 = 1000;
  TEST_2(get_32bit(value_14, 9), true);     // Check bit 9
  TEST_2(get_32bit(value_14, 31), false);   // Sign bit should be 0 for positive
  
  value_14 = set_32bit(value_14, 15);
  TEST_2(get_32bit(value_14, 15), true);    // bit 15 should be set
  
  int32_t value_15 = -1;                   // All bits set in two's complement
  TEST_2(count_32bit(value_15, true), 32);  // all 32 bits should be set
  TEST_2(count_32bit(value_15, false), 0);  // no bits should be unset

  // ==================== 64-BIT UNSIGNED INTEGER TESTS ====================
  // Testing: get_u64bit, set_u64bit, reset_u64bit, toggle_u64bit, xchg_u64bit, count_u64bit
  
  uint64_t value_16 = 0x0000000100000000ULL; // Bit 32 is set
  TEST_2(get_u64bit(value_16, 32), true);   // bit 32 should be 1
  TEST_2(get_u64bit(value_16, 0), false);   // bit 0 should be 0
  
  value_16 = set_u64bit(value_16, 0);
  TEST_2(get_u64bit(value_16, 0), true);    // bit 0 should be set
  
  value_16 = reset_u64bit(value_16, 32);
  TEST_2(get_u64bit(value_16, 32), false);  // bit 32 should be cleared
  TEST_2(count_u64bit(value_16, true), 1);  // should have 1 set bit

  uint64_t value_17 = 0xFFFFFFFFFFFFFFFFULL; // All bits set
  TEST_2(count_u64bit(value_17, true), 64); // should have 64 set bits
  
  value_17 = toggle_u64bit(value_17, 0);
  TEST_2(get_u64bit(value_17, 0), false);   // bit 0 should be toggled to 0
  TEST_2(count_u64bit(value_17, true), 63); // should have 63 set bits

  uint64_t value_18 = 0x8000000000000000ULL; // Only MSB (bit 63) is set
  TEST_2(get_u64bit(value_18, 63), true);   // bit 63 should be 1
  
  value_18 = xchg_u64bit(value_18, 63, 0); // exchange bits 63 and 0
  TEST_2(get_u64bit(value_18, 0), true);    // bit 0 should be 1
  TEST_2(get_u64bit(value_18, 63), false);  // bit 63 should be 0

  // ==================== 64-BIT SIGNED INTEGER TESTS ====================
  // Testing: get_64bit, set_64bit, reset_64bit, toggle_64bit, xchg_64bit, count_64bit
  
  int64_t value_19 = 1000000;
  TEST_2(count_64bit(value_19, true), 7);   // should have 7 set bits
  
  value_19 = set_64bit(value_19, 62);
  TEST_2(get_64bit(value_19, 62), true);    // bit 62 should be set
  
  int64_t value_20 = -256;                 // Two's complement representation
  TEST_2(get_64bit(value_20, 8), false);    // bit 8 should be 0
  
  value_20 = toggle_64bit(value_20, 32);
  TEST_2(get_64bit(value_20, 32), true);    // bit 32 should be toggled

  // generic tests for get_bit, set_bit, reset_bit, toggle_bit, xchg_bit using all values before

  TEST_2(get_bit(value_1, 3), true);    // bit 3 should still be 1
  TEST_2(get_bit(value_1, 2), false);   // bit 2 should be 0
  value_1 = set_bit(value_1, 2); // value_1: 1000-1101
  TEST_2(get_bit(value_1, 2), true); // bit 2 should now be 1
  value_1 = reset_bit(value_1, 3); // value_1: 1000-0101
  TEST_2(get_bit(value_1, 3), false); // bit 3 should now be 0
  value_1 = toggle_bit(value_1, 0); // value_1: 1000-0100
  TEST_2(get_bit(value_1, 0), false); // bit 0 should now be 0
  value_1 = xchg_bit(value_1, 7, 0); // value_1: 0000-0100
  TEST_2(get_bit(value_1, 7), false); // bit 7 should now be 0
  TEST_2(get_bit(value_1, 0), false); // bit 0 should still be 0
  TEST_2(count_bit(value_1, true), 1); // value_1 should have 1 set bit
  TEST_2(count_bit(value_1, false), 7); // value_1 should have 7 unset bits

EXIT_TEST(true);