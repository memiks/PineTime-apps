/*
 * Copyright (C) 2018 Koen Zandberg <koen@bergzand.net>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef APP_HAL
#define APP_HAL

#include <stdint.h>
#include "ili9341.h"
#include "event.h"

#include "hal_input.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * The Pinetime display requires color inversion on. This define disables it
 * after init for test setups with different displays
 */
#ifndef HAL_DISPLAY_DISABLE_INVERT_COLORS
#define HAL_DISPLAY_DISABLE_INVERT_COLORS   0
#endif

#ifndef HAL_DISPLAY_COLORS_BGR
#define HAL_DISPLAY_COLORS_BGR              0
#endif

#define HAL_DISPLAY_ROWS_VISIBLE            240
#define HAL_DISPLAY_ROWS_TOTAL              320

typedef enum {
    HAL_RESET_REASON_RESETPIN       = 0,
    HAL_RESET_REASON_WATCHDOG       = 1,
    HAL_RESET_REASON_SOFT_RESET     = 2,
    HAL_RESET_REASON_CPU_LOCKUP     = 3,
    HAL_RESET_REASON_GPIO_DETECT    = 16,
    HAL_RESET_REASON_LPCOMP         = 17,
    HAL_RESET_REASON_DEBUG_DETECT   = 18,
    HAL_RESET_REASON_NFC            = 19,
    HAL_RESET_REASON_ON_CHIP        = 255,
} hal_reset_reason_t;

typedef void display_t;

static inline void hal_display_flush(display_t *display, uint16_t x1,
                                     uint16_t x2, uint16_t y1, uint16_t y2,
                                     uint16_t *color)
{
    ili9341_t *disp = (ili9341_t*)display;
    ili9341_pixmap(disp, x1, x2, y1, y2, color);
}

display_t *hal_display_get_context(void);
void hal_display_scroll(uint16_t lines);

void hal_init(void);
void hal_display_on(void);
void hal_display_off(void);
void hal_set_button_cb(gpio_cb_t cb, void *arg);
uint32_t hal_battery_read_voltage(void);

/**
 * @brief retrieves the reset reason from the registers
 *
 * @note register is cleared after reading to prevent accumulating reset
 * reasons.
 */
int hal_battery_get_percentage(uint32_t voltage);

hal_reset_reason_t hal_get_reset_reason(void);
uint32_t hal_get_internal_temp(void);

/**
 * @brief check if the battery is currently being charged
 *
 * True when the power is connected and the battery is not fully charged
 *
 * @returns     true when the charger is active
 * @returns     false when the power is not connected or the battery is full
 */
bool hal_battery_is_charging(void);

/**
 * @brief check if the power is connected
 *
 * @returns     true when the power is connected
 * @returns     false when the board runs on battery power
 */
bool hal_battery_is_powered(void);

#ifdef __cplusplus
}
#endif

#endif /* APP_HAL */
