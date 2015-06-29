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
    void (* ShowOngoingNotification)(OngoingNotification* this_gen);

    void (* HideOngoingNotification)(OngoingNotification* this_gen);

    void (* SetOngoingNotificationTitle)(OngoingNotification* this_gen, char* title);

    void (* SetOngoingNotificationText)(OngoingNotification* this_gen, char* text);

    void (* SetOngoingNotificationIcon)(OngoingNotification* this_gen, char* imagePath);

} OngoingNotification;

OngoingNotification* NewOngoingNotification();

void DestroyOngoingNotification(OngoingNotification* this_gen);

void showOngoing(OngoingNotification* this_gen);

void hideOngoing(OngoingNotification* this_gen);

void setOngoingTitle(OngoingNotification* this_gen, char* title);

void setOngoingText(OngoingNotification* this_gen, char* text);

void setOngoingIcon(OngoingNotification* this_gen, char* imagePath);

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
