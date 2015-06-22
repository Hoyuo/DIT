/*
 * OngoingNotification.h
 *
 *  Created on: Jun 22, 2015
 *      Author: parksanghyun
 */



#ifndef DIT_ONGOINGNOTIFICATION_H
#define DIT_ONGOINGNOTIFICATION_H


#include <stdio.h>
#include <notification.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct _OngoingNotification OngoingNotification;


typedef struct _OngoingNotification {
    void (* create)(OngoingNotification* this_gen);

    void (* delete)(OngoingNotification* this_gen);

    void (* setTitle)(OngoingNotification* this_gen, char* title);

    void (* setText)(OngoingNotification* this_gen, char* text);

    void (* setIcon)(OngoingNotification* this_gen, char* imagePath);

} OngoingNotification;

OngoingNotification* newOngoingNotification();

void deleteOngoingNotification(OngoingNotification* this_gen);
void createOngoingNotification(OngoingNotification* this_gen);
void setOngoingNotificationTitle(OngoingNotification* this_gen, char* title);
void setOngoingNotificationText(OngoingNotification* this_gen, char* text);
void setOngoingNotificationIcon(OngoingNotification* this_gen, char* imagePath);


typedef struct _OngoingNotificationExtends{
    OngoingNotification Ongoingnotification;
    notification_h ongoingnotification_handle;
    char* title;
    char* text;
    char* imagepath;
} OngoingNotificationExtends;

#ifdef __cplusplus
}
#endif

#endif //DIT_OngoingNOTIFICATION_H
