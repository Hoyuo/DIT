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
    void (* ShowNotification)(Notification* this_gen);

    void (* HideNotification)(Notification* this_gen);

    void (* SetNotificationTitle)(Notification* this_gen, char* title);

    void (* SetNotificationText)(Notification* this_gen, char* text);

    void (* SetNotificationIcon)(Notification* this_gen, char* imagePath);

    void (* SetNotificationSound)(Notification* this_gen, char* soundpath);


} ;


Notification* NewNotification();

void DestroyNotification(Notification* this_gen);

void show(Notification* this_gen);

void hide(Notification* this_gen);

void setTitle(Notification* this_gen, char* title);

void setText(Notification* this_gen, char* text);

void setIcon(Notification* this_gen, char* imagePath);

void setSoundpath(Notification* this_gen, char* imagePath);


typedef struct {
    Notification notification;
    notification_h notification_handle;
    char* title;
    char* text;
    char* imagepath;
    char* soundpath;
    bool visible;
} NotificationExtend;

#ifdef __cplusplus
}
#endif

#endif //DIT_NOTIFICATION_H
