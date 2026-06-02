#include "clite/bitUtilitys.h"
#include <stdio.h>
#include <stdint.h>

int main() {
    printf("|========================================================|\n");
    printf("|        bitUtilitys Library - Practical Examples        |\n");
    printf("|========================================================|\n\n");

    // ============================================================
    // Example 1: GET_BIT - Reading individual bit values
    // ============================================================
    printf("EXAMPLE 1: Get Bit Operations\n");
    printf("---------------------------------\n");
    
    uint8_t number = 42;  // Binary: 0010-1010
    printf("Number: %d (Binary: ", number);
    for (int i = 7; i >= 0; i--) {
        printf("%d", get_u8bit(number, i) ? 1 : 0);
    }
    printf(")\n\n");
    
    printf("Reading individual bits:\n");
    for (int pos = 0; pos < 8; pos++) {
        printf("  Bit at position %d: %s\n", pos, get_u8bit(number, pos) ? "1" : "0");
    }
    printf("\n");

    // ============================================================
    // Example 2: SET_BIT - Setting bits to 1
    // ============================================================
    printf("EXAMPLE 2: Set Bit Operations\n");
    printf("--------------------------------\n");
    
    uint8_t flags = 0;  // Start with all zeros: 0000-0000
    printf("Initial value: %d (Binary: 0000-0000)\n", flags);
    
    // Set bit 0 (permission: read)
    flags = set_u8bit(flags, 0);
    printf("After setting bit 0: %d (Binary: ", flags);
    for (int i = 7; i >= 0; i--) printf("%d", get_u8bit(flags, i) ? 1 : 0);
    printf(") - READ permission\n");
    
    // Set bit 1 (permission: write)
    flags = set_u8bit(flags, 1);
    printf("After setting bit 1: %d (Binary: ", flags);
    for (int i = 7; i >= 0; i--) printf("%d", get_u8bit(flags, i) ? 1 : 0);
    printf(") - WRITE permission\n");
    
    // Set bit 2 (permission: execute)
    flags = set_u8bit(flags, 2);
    printf("After setting bit 2: %d (Binary: ", flags);
    for (int i = 7; i >= 0; i--) printf("%d", get_u8bit(flags, i) ? 1 : 0);
    printf(") - EXECUTE permission\n\n");

    // ============================================================
    // Example 3: RESET_BIT - Clearing bits to 0
    // ============================================================
    printf("EXAMPLE 3: Reset Bit Operations\n");
    printf("----------------------------------\n");
    
    uint8_t config = 255;  // All bits set: 1111-1111
    printf("Initial value: %d (Binary: 1111-1111)\n", config);
    
    config = reset_u8bit(config, 0);
    printf("After resetting bit 0: %d (Binary: ", config);
    for (int i = 7; i >= 0; i--) printf("%d", get_u8bit(config, i) ? 1 : 0);
    printf(")\n");
    
    config = reset_u8bit(config, 4);
    printf("After resetting bit 4: %d (Binary: ", config);
    for (int i = 7; i >= 0; i--) printf("%d", get_u8bit(config, i) ? 1 : 0);
    printf(")\n");
    
    config = reset_u8bit(config, 7);
    printf("After resetting bit 7: %d (Binary: ", config);
    for (int i = 7; i >= 0; i--) printf("%d", get_u8bit(config, i) ? 1 : 0);
    printf(")\n\n");

    // ============================================================
    // Example 4: TOGGLE_BIT - Flipping bit values
    // ============================================================
    printf("EXAMPLE 4: Toggle Bit Operations\n");
    printf("-----------------------------------\n");
    
    uint8_t state = 170;  // Binary: 1010-1010
    printf("Initial value: %d (Binary: ", state);
    for (int i = 7; i >= 0; i--) printf("%d", get_u8bit(state, i) ? 1 : 0);
    printf(")\n");
    
    state = toggle_u8bit(state, 0);
    printf("After toggling bit 0: %d (Binary: ", state);
    for (int i = 7; i >= 0; i--) printf("%d", get_u8bit(state, i) ? 1 : 0);
    printf(")\n");
    
    state = toggle_u8bit(state, 3);
    printf("After toggling bit 3: %d (Binary: ", state);
    for (int i = 7; i >= 0; i--) printf("%d", get_u8bit(state, i) ? 1 : 0);
    printf(")\n");
    
    state = toggle_u8bit(state, 7);
    printf("After toggling bit 7: %d (Binary: ", state);
    for (int i = 7; i >= 0; i--) printf("%d", get_u8bit(state, i) ? 1 : 0);
    printf(")\n\n");

    // ============================================================
    // Example 5: XCHG_BIT - Exchanging/Swapping bits
    // ============================================================
    printf("EXAMPLE 5: Exchange Bit Operations\n");
    printf("-------------------------------------\n");
    
    uint8_t data = 65;  // Binary: 0100-0001
    printf("Initial value: %d (Binary: ", data);
    for (int i = 7; i >= 0; i--) printf("%d", get_u8bit(data, i) ? 1 : 0);
    printf(")\n");
    printf("  Bit 0 = %d (position 0)\n", get_u8bit(data, 0) ? 1 : 0);
    printf("  Bit 6 = %d (position 6)\n\n", get_u8bit(data, 6) ? 1 : 0);
    
    data = xchg_u8bit(data, 0, 6);
    printf("After swapping bits 0 and 6: %d (Binary: ", data);
    for (int i = 7; i >= 0; i--) printf("%d", get_u8bit(data, i) ? 1 : 0);
    printf(")\n");
    printf("  Bit 0 = %d (now contains value from position 6)\n", get_u8bit(data, 0) ? 1 : 0);
    printf("  Bit 6 = %d (now contains value from position 0)\n\n", get_u8bit(data, 6) ? 1 : 0);

    // ============================================================
    // Example 6: COUNT_BIT - Counting set/unset bits
    // ============================================================
    printf("EXAMPLE 6: Count Bit Operations\n");
    printf("----------------------------------\n");
    
    uint16_t value = 2730;  // Binary: 1010-1010-1010 (alternating 1s and 0s)
    printf("Value: %d (Binary: ", value);
    for (int i = 15; i >= 0; i--) {
        printf("%d", get_u16bit(value, i) ? 1 : 0);
        if (i % 4 == 0) printf("-");
    }
    printf(")\n");
    
    int ones = count_u16bit(value, true);
    int zeros = count_u16bit(value, false);
    printf("Set bits (1s):   %d\n", ones);
    printf("Unset bits (0s): %d\n", zeros);
    printf("Total bits:      %d\n\n", ones + zeros);

    // ============================================================
    // Example 7: Practical Use Case - USB Device Permissions
    // ============================================================
    printf("EXAMPLE 7: Practical Use - USB Device Permissions\n");
    printf("------------------------------------------------------\n");
    
    // Using 8 bits to represent USB device permissions
    // Bit 0: Read from device
    // Bit 1: Write to device
    // Bit 2: Control transfer
    // Bit 3: Interrupt transfer
    // Bit 4: Bulk transfer
    // Bit 5: Isochronous transfer
    // Bit 6: Device eject
    // Bit 7: Reserved
    
    uint8_t usb_perms = 0;  // Start with no permissions
    
    usb_perms = set_u8bit(usb_perms, 0);  // Enable Read
    usb_perms = set_u8bit(usb_perms, 1);  // Enable Write
    usb_perms = set_u8bit(usb_perms, 4);  // Enable Bulk Transfer
    
    printf("USB Device Permissions: %d (Binary: ", usb_perms);
    for (int i = 7; i >= 0; i--) printf("%d", get_u8bit(usb_perms, i) ? 1 : 0);
    printf(")\n\n");
    
    printf("Permissions enabled:\n");
    if (get_u8bit(usb_perms, 0)) printf("  ✓ Read from device\n");
    if (get_u8bit(usb_perms, 1)) printf("  ✓ Write to device\n");
    if (get_u8bit(usb_perms, 2)) printf("  ✓ Control transfer\n");
    if (get_u8bit(usb_perms, 3)) printf("  ✓ Interrupt transfer\n");
    if (get_u8bit(usb_perms, 4)) printf("  ✓ Bulk transfer\n");
    if (get_u8bit(usb_perms, 5)) printf("  ✓ Isochronous transfer\n");
    if (get_u8bit(usb_perms, 6)) printf("  ✓ Device eject\n");
    
    printf("\nDisabling Write permission:\n");
    usb_perms = reset_u8bit(usb_perms, 1);
    if (!get_u8bit(usb_perms, 1)) printf("  ✓ Write permission successfully disabled\n");
    printf("\n");

    // ============================================================
    // Example 8: Working with 32-bit integers
    // ============================================================
    printf("EXAMPLE 8: 32-bit Integer Operations\n");
    printf("---------------------------------------\n");
    
    uint32_t status = 0x000000FF;  // Lower 8 bits set
    printf("Initial 32-bit value: 0x%08X\n", status);
    
    printf("Reading high bits:\n");
    printf("  Bit 24 = %d\n", get_u32bit(status, 24) ? 1 : 0);
    printf("  Bit 16 = %d\n", get_u32bit(status, 16) ? 1 : 0);
    printf("  Bit 8  = %d\n", get_u32bit(status, 8) ? 1 : 0);
    printf("  Bit 0  = %d\n", get_u32bit(status, 0) ? 1 : 0);
    
    status = set_u32bit(status, 16);  // Set bit 16
    printf("\nAfter setting bit 16: 0x%08X\n", status);
    
    status = toggle_u32bit(status, 8);  // Toggle bit 8
    printf("After toggling bit 8: 0x%08X\n\n", status);

    // ============================================================
    // Summary
    // ============================================================
    printf("|========================================================|\n");
    printf("|  bitUtilitys provides efficient bit-level operations:  |\n");
    printf("|  • get_*bit()   - Read individual bits                 |\n");
    printf("|  • set_*bit()   - Set bits to 1                        |\n");
    printf("|  • reset_*bit() - Clear bits to 0                      |\n");
    printf("|  • toggle_*bit()- Flip bit values                      |\n");
    printf("|  • xchg_*bit()  - Swap/exchange bits                   |\n");
    printf("|  • count_*bit() - Count set/unset bits                 |\n");
    printf("|                                                        |\n");
    printf("|  Supports: uint8, int8, uint16, int16, uint32, int32,  |\n");
    printf("|            uint64, int64, char, short, int, long       |\n");
    printf("|========================================================|\n");

    return 0;
}