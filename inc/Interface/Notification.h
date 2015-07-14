#ifndef DIT_NOTIFICATION_H
#define DIT_NOTIFICATION_H

#include <stdbool.h>
#include <stdalign.h>

#include <notification.h>

#include "dit.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _Notification * Notification;

struct _Notification
{
    void (* Show) (Notification this_gen);

    void (* Hide) (Notification this_gen);

    void (* setTitle) (Notification this_gen, String title);

    void (* setText) (Notification this_gen, String text);

    void (* setIcon) (Notification this_gen, String imagePath);

    void (* setSound) (Notification this_gen, String soundPath);

    void (* update) (Notification this_gen);
};

Notification NewNotification (void);

void DestroyNotification (Notification this_gen);

void NotificationShow (Notification this_gen);

void NotificationHide (Notification this_gen);

void setNotificationTitle (Notification this_gen, String title);

void setNotificationText (Notification this_gen, String text);

void setNotificationIcon (Notification this_gen, String imagePath);

void setNotificationSound (Notification this_gen, String soundPath);

void updateNotification (Notification this_gen);

typedef struct
{
    struct _Notification notification;
    notification_h       notification_handle;
    String               title;
    String               text;
    String               imagePath;
    String               soundPath;
    bool                 visible;
}    NotificationExtend;

#ifdef __cplusplus
}
#endif

#endif //DIT_NOTIFICATION_H
