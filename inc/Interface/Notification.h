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
    void (* showNotification)(Notification* this);

    void (* hideNotification)(Notification* this);

    void (* setNotificationTitle)(Notification* this, char* title);

    void (* setNotificationText)(Notification* this, char* text);

    void (* setNotificationIcon)(Notification* this, char* imagePath);

} Notification;


Notification* newNotification();

//destroyer
void deleteNotification(Notification* this);



void show(Notification* this);

void hide(Notification* this);

void setTitle(Notification* this, char* title);

void setText(Notification* this, char* text);

void setIcon(Notification* this, char* imagePath);

typedef struct {
    Notification notification;
    notification_h notification_handle;
    char* title;
    char* text;
    char* imagepath;

} NotificationExtend;

#ifdef __cplusplus
}
#endif

#endif //DIT_NOTIFICATION_H
