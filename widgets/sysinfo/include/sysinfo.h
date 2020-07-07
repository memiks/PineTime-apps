/*
 * Copyright (C) 2020 Koen Zandberg <koen@bergzand.net>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef WIDGET_SYSINFO_H
#define WIDGET_SYSINFO_H

#include "lvgl.h"
#include "widget.h"
#include "controller.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _sysinfo_widget {
    widget_t widget;
    control_event_handler_t handler;
    lv_obj_t *screen;
    lv_obj_t *info_label;
    lv_obj_t *page;
    uint64_t uptime;
    uint32_t temperature;
    const char *reset_string;
    uint16_t battery_voltage;
    bool powered;
    bool charging;
} sysinfo_widget_t;


#ifdef __cplusplus
}
#endif

#endif /* WIDGET_SYSINFO_H */

