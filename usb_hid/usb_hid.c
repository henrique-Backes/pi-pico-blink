/** @file usb_hid.c
*
* @brief Implementation for USB HID Consumer Control (Media Keys).
*
* @par
* COPYRIGHT NOTICE: (c) 2026. All rights reserved.
*/
#include <string.h>
#include "tusb.h"
#include "usb_hid.h"

tusb_desc_device_t const desc_device =
{
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0200,
    .bDeviceClass       = 0x00,
    .bDeviceSubClass    = 0x00,
    .bDeviceProtocol    = 0x00,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
    .idVendor           = 0xCafe,
    .idProduct          = 0x0001,
    .bcdDevice          = 0x0100,
    .iManufacturer      = 0x01,
    .iProduct           = 0x02,
    .iSerialNumber      = 0x03,
    .bNumConfigurations = 0x01
};

enum
{
    ITF_NUM_HID,
    ITF_NUM_TOTAL
};

#define CONFIG_ID_TOTAL_LEN (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)

uint8_t const desc_hid_report[] =
{
    TUD_HID_REPORT_DESC_CONSUMER()
};

uint8_t const desc_configuration[] =
{
    TUD_CONFIG_DESCRIPTOR(1u, ITF_NUM_TOTAL, 0u, CONFIG_ID_TOTAL_LEN, 
                          TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100u),
    TUD_HID_DESCRIPTOR(ITF_NUM_HID, 0u, HID_ITF_PROTOCOL_NONE, 
                       sizeof(desc_hid_report), 0x81, CFG_TUD_HID_EP_BUFSIZE, 10u)
};

char const * string_desc_arr[] =
{
    (const char[]) { 0x09, 0x04 },
    "TinyUSB",
    "Pico StreamDeck",
    "123456"
};

static uint16_t g_desc_str[32];

/*!
* @brief Device descriptor callback.
*
* @return Pointer to device descriptor.
*/
uint8_t const *
tud_descriptor_device_cb (void)
{
    return ((uint8_t const *) &desc_device);
}

/*!
* @brief Configuration descriptor callback.
*
* @param[in] index Configuration index.
*
* @return Pointer to configuration descriptor.
*/
uint8_t const *
tud_descriptor_configuration_cb (uint8_t index)
{
    (void) index;
    return (desc_configuration);
}

/*!
* @brief String descriptor callback.
*
* @param[in] index String index.
* @param[in] langid Language ID.
*
* @return Pointer to string descriptor.
*/
uint16_t const *
tud_descriptor_string_cb (uint8_t index, uint16_t langid)
{
    (void) langid;
    uint8_t chr_count;

    if (0 == index)
    {
        memcpy(&g_desc_str[1], string_desc_arr[0], 2);
        chr_count = 1;
    }
    else
    {
        if (index >= (sizeof(string_desc_arr) / sizeof(string_desc_arr[0]))) 
        {
            return (NULL);
        }

        const char * str = string_desc_arr[index];
        chr_count = (uint8_t) strlen(str);

        if (chr_count > 31) 
        {
            chr_count = 31;
        }

        for (uint8_t i = 0; i < chr_count; i++)
        {
            g_desc_str[1 + i] = str[i];
        }
    }

    g_desc_str[0] = (TUSB_DESC_STRING << 8) | (2 * chr_count + 2);
    return (g_desc_str);
}

/*!
* @brief Report descriptor callback.
*
* @param[in] itf Interface number.
*
* @return Pointer to report descriptor.
*/
uint8_t const *
tud_hid_descriptor_report_cb (uint8_t itf)
{
    (void) itf;
    return (desc_hid_report);
}

/*!
* @brief HID Get Report callback.
*/
uint16_t
tud_hid_get_report_cb (uint8_t itf, uint8_t report_id, hid_report_type_t report_type, 
                       uint8_t * buffer, uint16_t reqlen)
{
    (void) itf;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;

    return (0u);
}

/*!
* @brief HID Set Report callback.
*/
void
tud_hid_set_report_cb (uint8_t itf, uint8_t report_id, hid_report_type_t report_type, 
                       uint8_t const * buffer, uint16_t bufsize)
{
    (void) itf;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) bufsize;
}

/*!
* @brief Initializes the TinyUSB stack.
*/
void
usb_hid_init (void)
{
    tusb_init();
}

/*!
* @brief Sends Volume Up command.
*/
void
hid_send_volume_up (bool state)
{
    uint16_t report_val = (state) ? HID_USAGE_CONSUMER_VOLUME_INCREMENT : 0u;

    if (tud_hid_ready())
    {
        tud_hid_report(0u, &report_val, sizeof(report_val));
        sleep_ms(2u);
    }
}

/*!
* @brief Sends Volume Down command.
*/
void
hid_send_volume_down (bool state)
{
    uint16_t report_val = (state) ? HID_USAGE_CONSUMER_VOLUME_DECREMENT : 0u;

    if (tud_hid_ready())
    {
        tud_hid_report(0u, &report_val, sizeof(report_val));
        sleep_ms(2u);
    }
}

/*!
* @brief Sends Play/Pause command.
*/
void
hid_send_play_pause (bool state)
{
    uint16_t report_val = (state) ? HID_USAGE_CONSUMER_PLAY_PAUSE : 0u;

    if (tud_hid_ready())
    {
        tud_hid_report(0u, &report_val, sizeof(report_val));
        sleep_ms(2u);
    }
}
/*** end of file ***/
