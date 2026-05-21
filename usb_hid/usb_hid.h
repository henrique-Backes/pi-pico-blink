/** @file usb_hid.h
*
* @brief USB HID Consumer Control (Media Keys) module.
*
* @par
* COPYRIGHT NOTICE: (c) 2026. All rights reserved.
*/
#ifndef USB_HID_H
#define USB_HID_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * @brief Initializes the TinyUSB stack.
 */
void usb_hid_init (void);

/*
 * @brief Sends Volume Up command.
 * 
 * @param[in] state true for pressed, false for released.
 */
void hid_send_volume_up (bool state);

/*
 * @brief Sends Volume Down command.
 * 
 * @param[in] state true for pressed, false for released.
 */
void hid_send_volume_down (bool state);

/*
 * @brief Sends Play/Pause command.
 * 
 * @param[in] state true for pressed, false for released.
 */
void hid_send_play_pause (bool state);

#ifdef __cplusplus
}
#endif

#endif /* USB_HID_H */
/*** end of file ***/
