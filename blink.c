/** @file blink.c
*
* @brief Main application for the Stream Deck with edge detection.
*
* @par
* COPYRIGHT NOTICE: (c) 2026. All rights reserved.
*/
#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "tusb.h"
#include "configs.h"
#include "keypad.h"
#include "usb_hid.h"

/*!
* @brief Entry point for the Stream Deck application.
*/
int
main (void)
{
    uint16_t key_mask;
    uint16_t last_key_mask = 0u;

    keypad_init();
    usb_hid_init();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    for (;;)
    {
        tud_task();

        key_mask = keypad_scan();

        /* Only process HID reports if the state has changed to avoid spamming */
        if (key_mask != last_key_mask)
        {
            /* Volume Up (Key A) */
            if ((key_mask & KEY_MASK_A) != (last_key_mask & KEY_MASK_A))
            {
                hid_send_volume_up(0u != (key_mask & KEY_MASK_A));
            }

            /* Volume Down (Key B) */
            if ((key_mask & KEY_MASK_B) != (last_key_mask & KEY_MASK_B))
            {
                hid_send_volume_down(0u != (key_mask & KEY_MASK_B));
            }

            /* Play/Pause (Key C) */
            if ((key_mask & KEY_MASK_C) != (last_key_mask & KEY_MASK_C))
            {
                hid_send_play_pause(0u != (key_mask & KEY_MASK_C));
            }

            /* Feedback visual apenas na pressao */
            if (KEY_MASK_NONE != key_mask)
            {
                gpio_put(LED_PIN, 1);
                sleep_ms(20u);
                gpio_put(LED_PIN, 0);
            }

            last_key_mask = key_mask;
        }

        /* Small delay for debounce and CPU health */
        sleep_ms(10u);
    }
}
/*** end of file ***/
