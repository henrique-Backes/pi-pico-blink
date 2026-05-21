/** @file tusb_config.h
*
* @brief TinyUSB configuration file.
*
* @par
* COPYRIGHT NOTICE: (c) 2026. All rights reserved.
*/
#ifndef TUSB_CONFIG_H
#define TUSB_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#define CFG_TUSB_RHPORT0_MODE   (OPT_MODE_DEVICE | OPT_MODE_FULL_SPEED)

#define CFG_TUD_HID             1u
#define CFG_TUD_CDC             0u
#define CFG_TUD_MSC             0u
#define CFG_TUD_MIDI            0u
#define CFG_TUD_VENDOR          0u

#define CFG_TUD_HID_EP_BUFSIZE  64u

#ifdef __cplusplus
}
#endif

#endif /* TUSB_CONFIG_H */
/*** end of file ***/
