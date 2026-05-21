/** @file keypad.c
*
* @brief Implementation for the 4x4 matrix keypad scanner using Pin Inversion.
*
* @par
* COPYRIGHT NOTICE: (c) 2026. All rights reserved.
*/
#include "pico/stdlib.h"
#include "configs.h"
#include "keypad.h"

static const uint8_t g_row_pins[KEYPAD_ROWS] = 
{
    PIN_ROW_1, PIN_ROW_2, PIN_ROW_3, PIN_ROW_4
};

static const uint8_t g_col_pins[KEYPAD_COLS] = 
{
    PIN_COL_1, PIN_COL_2, PIN_COL_3, PIN_COL_4
};

static const uint16_t g_key_bitmasks[KEYPAD_ROWS][KEYPAD_COLS] = 
{
    {KEY_MASK_1,    KEY_MASK_2,    KEY_MASK_3,    KEY_MASK_A},
    {KEY_MASK_4,    KEY_MASK_5,    KEY_MASK_6,    KEY_MASK_B},
    {KEY_MASK_7,    KEY_MASK_8,    KEY_MASK_9,    KEY_MASK_C},
    {KEY_MASK_STAR, KEY_MASK_0,    KEY_MASK_HASH, KEY_MASK_D}
};

/*!
* @brief Set all keypad pins to a safe passive state.
*/
static void
keypad_reset_pins (void)
{
    uint8_t i;

    for (i = 0u; i < KEYPAD_ROWS; i++)
    {
        gpio_set_dir(g_row_pins[i], GPIO_IN);
        gpio_pull_up(g_row_pins[i]);
    }

    for (i = 0u; i < KEYPAD_COLS; i++)
    {
        gpio_set_dir(g_col_pins[i], GPIO_IN);
        gpio_pull_up(g_col_pins[i]);
    }
}

/*!
* @brief Initialize keypad GPIOs.
*/
void
keypad_init (void)
{
    uint8_t i;

    for (i = 0u; i < KEYPAD_ROWS; i++)
    {
        gpio_init(g_row_pins[i]);
    }

    for (i = 0u; i < KEYPAD_COLS; i++)
    {
        gpio_init(g_col_pins[i]);
    }

    keypad_reset_pins();
}

/*!
* @brief Scan the keypad matrix using Row-Column Inversion.
*
* @return A 16-bit mask representing all currently pressed keys.
*/
uint16_t
keypad_scan (void)
{
    int8_t   col_idx = -1;
    int8_t   row_idx = -1;
    uint8_t  i;
    uint16_t result  = KEY_MASK_NONE;

    for (i = 0u; i < KEYPAD_ROWS; i++)
    {
        gpio_set_dir(g_row_pins[i], GPIO_OUT);
        gpio_put(g_row_pins[i], 0);
    }

    for (i = 0u; i < KEYPAD_COLS; i++)
    {
        gpio_set_dir(g_col_pins[i], GPIO_IN);
        gpio_pull_up(g_col_pins[i]);
    }

    sleep_us(5u);

    for (i = 0u; i < KEYPAD_COLS; i++)
    {
        if (0 == gpio_get(g_col_pins[i]))
        {
            col_idx = (int8_t) i;
            break;
        }
    }

    if (col_idx >= 0)
    {
        for (i = 0u; i < KEYPAD_COLS; i++)
        {
            gpio_set_dir(g_col_pins[i], GPIO_OUT);
            gpio_put(g_col_pins[i], 0);
        }

        for (i = 0u; i < KEYPAD_ROWS; i++)
        {
            gpio_set_dir(g_row_pins[i], GPIO_IN);
            gpio_pull_up(g_row_pins[i]);
        }

        sleep_us(5u);

        for (i = 0u; i < KEYPAD_ROWS; i++)
        {
            if (0 == gpio_get(g_row_pins[i]))
            {
                row_idx = (int8_t) i;
                break;
            }
        }
    }

    if ((col_idx >= 0) && (row_idx >= 0))
    {
        result = g_key_bitmasks[row_idx][col_idx];
    }

    keypad_reset_pins();

    return (result);
}
/*** end of file ***/
