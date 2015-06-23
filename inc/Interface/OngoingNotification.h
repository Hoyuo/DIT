/*
 * OngoingNotification.h
 *
 *  Created on: Jun 22, 2015
 *      Author: parksanghyun
 */

#ifndef DIT_ONGOINGNOTIFICATION_H
#define DIT_ONGOINGNOTIFICATION_H

#include <stdbool.h>
#include <stdalign.h>
#include <notification.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct _OngoingNotification OngoingNotification;


typedef struct _OngoingNotification {
    void (* create)(OngoingNotification* this);

    void (* delete)(OngoingNotification* this);

    void (* setTitle)(OngoingNotification* this, char* title);

    void (* setText)(OngoingNotification* this, char* text);

    void (* setIcon)(OngoingNotification* this, char* imagePath);

} OngoingNotification;

OngoingNotification* newOngoingNotification();

void deleteOngoingNotification(OngoingNotification* this);
void createOngoingNotification(OngoingNotification* this);
void setOngoingNotificationTitle(OngoingNotification* this, char* title);
void setOngoingNotificationText(OngoingNotification* this, char* text);
void setOngoingNotificationIcon(OngoingNotification* this, char* imagePath);

typedef struct _OngoingNotificationExtend {
    OngoingNotification Ongoingnotification;
    notification_h ongoingnotification_handle;
    char* title;
    char* text;
    char* imagepath;
} OngoingNotificationExtend;

#ifdef __cplusplus
}
#endif

#endif //DIT_OngoingNOTIFICATION_H
