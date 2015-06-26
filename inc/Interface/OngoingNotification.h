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
    void (* ShowOngoingNotification)(OngoingNotification* this);

    void (* HideOngoingNotification)(OngoingNotification* this);

    void (* SetOngoingNotificationTitle)(OngoingNotification* this, char* title);

    void (* SetOngoingNotificationText)(OngoingNotification* this, char* text);

    void (* SetOngoingNotificationIcon)(OngoingNotification* this, char* imagePath);

} OngoingNotification;

//constructor
OngoingNotification* NewOngoingNotification();

//destroyer
void DestroyOngoingNotification(OngoingNotification* this);


void showOngoing(OngoingNotification* this);

void hideOngoing(OngoingNotification* this);

void setOngoingTitle(OngoingNotification* this, char* title);

void setOngoingText(OngoingNotification* this, char* text);

void setOngoingIcon(OngoingNotification* this, char* imagePath);

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
