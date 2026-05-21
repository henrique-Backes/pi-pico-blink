/** @file keypad.h
*
* @brief Interface for the 4x4 matrix keypad scanner with multi-key support.
*
* @par
* COPYRIGHT NOTICE: (c) 2026. All rights reserved.
*/
#ifndef KEYPAD_H
#define KEYPAD_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define KEY_MASK_NONE  0x0000u
#define KEY_MASK_1     0x0001u
#define KEY_MASK_2     0x0002u
#define KEY_MASK_3     0x0004u
#define KEY_MASK_A     0x0008u
#define KEY_MASK_4     0x0010u
#define KEY_MASK_5     0x0020u
#define KEY_MASK_6     0x0040u
#define KEY_MASK_B     0x0080u
#define KEY_MASK_7     0x0100u
#define KEY_MASK_8     0x0200u
#define KEY_MASK_9     0x0400u
#define KEY_MASK_C     0x0800u
#define KEY_MASK_STAR  0x1000u
#define KEY_MASK_0     0x2000u
#define KEY_MASK_HASH  0x4000u
#define KEY_MASK_D     0x8000u

/*
 * @brief Initializes the GPIO pins for the keypad matrix.
 */
void keypad_init (void);

/*
 * @brief Scans the keypad matrix for key presses.
 *
 * @return A 16-bit mask representing all currently pressed keys.
 */
uint16_t keypad_scan (void);

#ifdef __cplusplus
}
#endif

#endif /* KEYPAD_H */
/*** end of file ***/
