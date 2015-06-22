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


#ifdef __cplusplus
extern "C" {
#endif


typedef struct _Notification Notification;


typedef struct _Notification {
    void (* create)(Notification* this);

    void (* delete)(Notification* this);

    void (* setTitle)(Notification* this, char* title);

    void (* setText)(Notification* this, char* text);

    void (* setIcon)(Notification* this, char* imagePath);

} Notification;


Notification* newNotification();
void deleteNotification(Notification* this);
void createNotification(Notification* this);
void setNotificationTitle(Notification* this, char* title);
void setNotificationText(Notification* this, char* text);
void setNotificationIcon(Notification* this, char* imagePath);


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
