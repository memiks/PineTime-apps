/*
 * Copyright (C) 2019 Koen Zandberg <koen@bergzand.net>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef APP_BLEMAN_H
#define APP_BLEMAN_H

#include "host/ble_gap.h"
#include <stdint.h>
#include "event.h"
#include "ts_event.h"
#include "widget.h"
#include "thread.h"
#include "xtimer.h"
#include "bleman/bas.h"
#include "bleman/hrs.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CONFIG_BLEMAN_DEVICE_NAME
#define CONFIG_BLEMAN_DEVICE_NAME   "RIOT Watch"
#endif

#ifndef CONFIG_BLEMAN_MANUF_NAME
#define CONFIG_BLEMAN_MANUF_NAME     "BosMoment"
#endif

#ifndef CONFIG_BLEMAN_MODEL_NUM
#define CONFIG_BLEMAN_MODEL_NUM     "1A"
#endif

#ifndef CONFIG_BLEMAN_FW_VERSION
#define CONFIG_BLEMAN_FW_VERSION    "1.0.0-alpha1"
#endif

#ifndef CONFIG_BLEMAN_HW_VERSION
#define CONFIG_BLEMAN_HW_VERSION    "1"
#endif

#ifndef CONFIG_BLEMAN_SERIAL_LEN
#define CONFIG_BLEMAN_SERIAL_LEN    24
#endif

#ifndef CONFIG_BLEMAN_PINETIME_UUID
#define CONFIG_BLEMAN_PINETIME_UUID 0xc5, 0xb1, 0x8c, 0x78, 0x38, 0x3b, 0x46, 0x56, 0x99, 0x13, 0x4a, 0xb0, 0x0a, 0xdc, 0x51, 0x98
#endif

typedef struct _bleman bleman_t;
typedef struct _bleman_event_handler bleman_event_handler_t;

/**
 * @brief event notification handler
 *
 * @param   event       NimBLE gap event
 * @param   bleman      bleman context
 * @param   arg         Extra argument passed to the call
 */
typedef void (*bleman_event_cb_t)(bleman_t *bleman, struct ble_gap_event *event,
                                  void *arg);

typedef enum {
    BLEMAN_BLE_STATE_INACTIVE,
    BLEMAN_BLE_STATE_ADVERTISING,
    BLEMAN_BLE_STATE_DISCONNECTED,
    BLEMAN_BLE_STATE_CONNECTED,
} bleman_ble_state_t;

struct _bleman_event_handler {
    struct _bleman_event_handler *next; /**< linked list iterator */
    bleman_event_cb_t handler; /**< Handler function pointer */
    void *arg; /**< Argument passed to the handler function call */
};

struct _bleman {
    char serial[CONFIG_BLEMAN_SERIAL_LEN];
    event_queue_t eq;
    uint16_t conn_handle;
    bleman_event_handler_t *handlers;
    bleman_ble_state_t state;
    bleman_bas_t bas;
    bleman_hrs_t hrs;
};

int bleman_thread_create(void);

bleman_t *bleman_get(void);
bleman_ble_state_t bleman_get_conn_state(bleman_t *bleman, struct ble_gap_conn_desc *state);

/**
 * @brief Add a notification handler to the bleman thread
 *
 * @param   bleman  bleman context
 * @param   event   event handler context to add
 * @param   cb      callback function
 * @param   arg     argument to add to the handler
 */
void bleman_add_event_handler(bleman_t *bleman, bleman_event_handler_t *event,
                              bleman_event_cb_t cb, void *arg);

#ifdef __cplusplus
}
#endif

#endif /* APP_BLEMAN_H */
