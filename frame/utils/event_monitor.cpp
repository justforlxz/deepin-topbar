/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2011 ~ 2017 Deepin, Inc.
 *               2011 ~ 2017 Wang Yong
 *
 * Author:     Wang Yong <wangyong@deepin.com>
 * Maintainer: Wang Yong <wangyong@deepin.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "event_monitor.h"
#include <X11/Xlibint.h>

EventMonitor::EventMonitor(QObject *parent) : QThread(parent)
{
    isPress = false;
}

void EventMonitor::run()
{
    Display* display = XOpenDisplay(0);
    if (display == 0) {
        fprintf(stderr, "unable to open display\n");
        return;
    }

    // Receive from ALL clients, including future clients.
    XRecordClientSpec clients = XRecordAllClients;
    XRecordRange* range = XRecordAllocRange();
    if (range == 0) {
        fprintf(stderr, "unable to allocate XRecordRange\n");
        return;
    }

    // Receive KeyPress, KeyRelease, ButtonPress, ButtonRelease and MotionNotify events.
    memset(range, 0, sizeof(XRecordRange));
    range->device_events.first = KeyPress;
    range->device_events.last  = MotionNotify;

    // And create the XRECORD context.
    XRecordContext context = XRecordCreateContext(display, 0, &clients, 1, &range, 1);
    if (context == 0) {
        fprintf(stderr, "XRecordCreateContext failed\n");
        return;
    }
    XFree(range);

    XSync(display, True);

    Display* display_datalink = XOpenDisplay(0);
    if (display_datalink == 0) {
        fprintf(stderr, "unable to open second display\n");
        return;
    }

    if (!XRecordEnableContext(display_datalink, context,  callback, (XPointer) this)) {
        fprintf(stderr, "XRecordEnableContext() failed\n");
        return;
    }
}

void EventMonitor::callback(XPointer ptr, XRecordInterceptData* data)
{
    ((EventMonitor *) ptr)->handleRecordEvent(data);
}

void EventMonitor::handleRecordEvent(XRecordInterceptData* data)
{
    if (data->category == XRecordFromServer) {
        xEvent * event = (xEvent *)data->data;
        switch (event->u.u.type) {
        case ButtonPress:
            if (filterWheelEvent(event->u.u.detail)) {
                isPress = true;
                emit buttonPress(
                    event->u.keyButtonPointer.rootX, 
                    event->u.keyButtonPointer.rootY);
            }
            
            break;
        case MotionNotify:
            if (isPress) {
                emit buttonDrag(
                    event->u.keyButtonPointer.rootX, 
                    event->u.keyButtonPointer.rootY);
            }
            
            break;
        case ButtonRelease:
            if (filterWheelEvent(event->u.u.detail)) {
                isPress = false;
                emit buttonRelease(
                    event->u.keyButtonPointer.rootX, 
                    event->u.keyButtonPointer.rootY);
            }
            
            break;
        case KeyPress:
            emit keyPress(((unsigned char*) data->data)[1]);
            
            break;
        case KeyRelease:
            emit keyRelease(((unsigned char*) data->data)[1]);
            
            break;
        default:
            break;
        }
    }

    fflush(stdout);
    XRecordFreeData(data);
}

bool EventMonitor::filterWheelEvent(int detail)
{
    return detail != WheelUp && detail != WheelDown && detail != WheelLeft && detail != WheelRight;
}
