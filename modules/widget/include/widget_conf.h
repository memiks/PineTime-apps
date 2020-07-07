/*
 * Copyright (C) 2018 Koen Zandberg <koen@bergzand.net>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef APP_WIDGET_CONF
#define APP_WIDGET_CONF

#include "widget.h"

#include "time_conf.h"
#include "menu_tiles_conf.h"

#ifdef __cplusplus
extern "C" {
#endif

#if MODULE_WIDGET_SYSINFO
#include "sysinfo.h"
extern sysinfo_widget_t sysinfo_widget;
#define WIDGET_SYSINFO (&sysinfo_widget.widget)
#endif

#if MODULE_WIDGET_FACE_NOTIFICATION
#include "face_notification.h"
extern face_notification_widget_t face_notification_widget;
#define WIDGET_FACE_NOTIF (&face_notification_widget.widget)
#endif

#if MODULE_WIDGET_FACE_SPORTS
#include "face_sports.h"
extern face_sports_widget_t face_sports_widget;
#define WIDGET_FACE_SPORTS (&face_sports_widget.widget)
#endif

/**
 * @brief Home widget, shown when display is turned on.
 *        Fullfills the task of home screen
 */
#ifndef CONFIG_WIDGET_HOME
#define CONFIG_WIDGET_HOME WIDGET_HOME_TIME
#endif /* WIDGET_HOME */

#ifndef CONFIG_WIDGET_MENU
#define CONFIG_WIDGET_MENU WIDGET_MENU_TILES
#endif /* CONFIG_WIDGET_MENU */

static const widget_map_t widgets_installed[] = {
#if MODULE_WIDGET_SYSINFO
    WIDGET_SYSINFO,
#endif
};

static const widget_map_t widget_faces_installed[] = {
    CONFIG_WIDGET_HOME,
#if MODULE_WIDGET_FACE_NOTIFICATION
    WIDGET_FACE_NOTIF,
#endif
#if MODULE_WIDGET_FACE_SPORTS
    WIDGET_FACE_SPORTS,
#endif
};

static const size_t widget_faces_num = ARRAY_SIZE(widget_faces_installed);

#ifdef __cplusplus
}
#endif

#endif /* APP_WIDGET_CONF */
