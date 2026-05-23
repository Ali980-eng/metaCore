#include "CLite.h"

MAIN_TEST("clut")

  // UTEST[1]: 5 tests
  uint8_t value_1 = 8; // value_1: 0000-1000
  TEST2(get_u8bit(value_1, 0), false)
  TEST2(get_u8bit(value_1, 3), true)
  TEST2(get_u8bit(value_1, 7), false)
  value_1 = set_u8bit(value_1, 0); // value_1: 0000-1001
  TEST2(get_u8bit(value_1, 0), true)
  value_1 = set_u8bit(value_1, 7); // value_1: 1000-1001
  TEST2(get_u8bit(value_1, 7), true)
  
  // UTEST[2]: 5 tests
  uint8_t value_2 = 99; // value_2: 0110-0011
  TEST2(get_u8bit(value_2, 6), true)
  value_2 = reset_u8bit(value_2, 6);// value_2: 0010-0011
  TEST2(get_u8bit(value_2, 6), false)
  value_2 = set_u8bit(value_2, 7); // value_2: 1010-0011
  TEST2(get_u8bit(value_2, 7), true)
  value_2 = set_u8bit(value_2, 3); // value_2: 1010-1011
  TEST2(get_u8bit(value_2, 3), true)
  value_2 = reset_u8bit(value_2, 1); // value_2: 1010-1001
  TEST2(get_u8bit(value_2, 1), false)

  // UTEST[3]: 5 tests
  uint8_t value_3 = 16; // value_3: 0001-0000
  TEST2(get_u8bit(value_3, 0), false)
  TEST2(get_u8bit(value_3, 4), true)
  value_3 = xchg_u8bit(value_3, 4, 0); // value_3: 0000-0001
  TEST2(get_u8bit(value_3, 0), true)
  TEST2(get_u8bit(value_3, 4), false)
  value_3 = reset_u8bit(value_3, 0); // value_3: 0000-0000
  TEST2(value_3, 0)

  // UTEST[4]: 5 tests
  uint8_t value_4 = 35; // value_4: 0010-0011
  TEST2(get_u8bit(value_4, 0), true)
  TEST2(get_u8bit(value_4, 7), false)
  value_4 = toggle_u8bit(value_4, 0); // value_4: 0010-0010
  TEST2(get_u8bit(value_4, 0), false)
  value_4 = toggle_u8bit(value_4, 7); // value_4: 1010-0010
  TEST2(get_u8bit(value_4, 7), true)
  value_4 = xchg_u8bit(value_4, 5, 0); // value_4: 1000-0011
  TEST2(get_u8bit(value_4, 5), false)

  // UTEST[5]: 5 tests
  TEST2(count_u8bit(value_1, true), 3)
  TEST2(count_u8bit(value_2, true), 4)
  TEST2(count_u8bit(value_3, true), 0)
  TEST2(count_u8bit(value_3, false), 8)
  TEST2(count_u8bit(value_4, false), 5)

  // UTEST[6]: 5 tests
  int8_t value_5 = -2;
  TEST2(get_8bit(value_5, 0), false)
  value_5 = set_8bit(value_5, 0);
  TEST2(get_8bit(value_5, 0), true)
  TEST2(get_8bit(value_5, 5), true)
  value_5 = toggle_8bit(value_5, 5);
  TEST2(get_8bit(value_5, 5), false)
  TEST2(count_8bit(value_5, true), 7)

  // UTEST[7]:
  int8_t value_6 = 88;

EXIT_TEST(true)