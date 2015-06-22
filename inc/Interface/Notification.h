/*
 * Notification.h
 *
 *  Created on: Jun 22, 2015
 *      Author: parksanghyun
 */



#ifndef DIT_NOTIFICATION_H
#define DIT_NOTIFICATION_H

#include <stdbool.h>
#include <stdalign.h>
#include <notification.h>


#ifdef __cplusplus
extern "C" {
#endif


typedef struct _Notification Notification;


typedef struct _Notification {
    void (* create)(Notification* this);

    void (* delete)(Notification* this_gen);

    void (* setTitle)(Notification* this_gen, char* title);

    void (* setText)(Notification* this_gen, char* text);

    void (* setIcon)(Notification* this_gen, char* imagePath);

} Notification;


Notification* newNotification();
void deleteNotification(Notification* this_gen);
void createNotification(Notification* this_gen);
void setNotificationTitle(Notification* this_gen, char* title);
void setNotificationText(Notification* this_gen, char* text);
void setNotificationIcon(Notification* this_gen, char* imagePath);


typedef struct {
    Notification notification;
    notification_h notification_handle;
    char* title;
    char* text;
    char* imagePath;

} NotificationExtend;

#ifdef __cplusplus
}
#endif

#endif //DIT_NOTIFICATION_H
