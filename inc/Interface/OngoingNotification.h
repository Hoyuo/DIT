#ifndef DIT_ONGOINGNOTIFICATION_H
#define DIT_ONGOINGNOTIFICATION_H

#include <stdbool.h>
#include <stdalign.h>

#include <notification.h>

#include "dit.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _OngoingNotification * OngoingNotification;

struct _OngoingNotification
{
    void (* Show) (OngoingNotification this_gen);

    void (* Hide) (OngoingNotification this_gen);

    void (* setTitle) (OngoingNotification this_gen, String title);

    void (* setText) (OngoingNotification this_gen, String text);

    void (* setIcon) (OngoingNotification this_gen, String imagePath);

    void (* setSound) (OngoingNotification this_gen, String soundPath);

    void (* setProgress) (OngoingNotification this_gen, double progress);

    void (* update) (OngoingNotification this_gen);
};

OngoingNotification NewOngoingNotification ();

void DestroyOngoingNotification (OngoingNotification this_gen);

void OngoingNotificationShow (OngoingNotification this_gen);

void OngoingNotificationHide (OngoingNotification this_gen);

void setOngoingNotificationTitle (OngoingNotification this_gen, String title);

void setOngoingNotificationText (OngoingNotification this_gen, String text);

void setOngoingNotificationIcon (OngoingNotification this_gen, String imagePath);

void setOngoingNotificationSound (OngoingNotification this_gen, String soundPath);

void setOngoingNotificationProgress (OngoingNotification this_gen, double progress);

void updateOngoingNotification (OngoingNotification this_gen);

typedef struct _OngoingNotificationExtend
{
    struct _OngoingNotification Ongoingnotification;
    notification_h              ongoingnotification_handle;
    String                      title;
    String                      text;
    String                      imagePath;
    String                      soundPath;
    bool                        visible;
}    OngoingNotificationExtend;

#ifdef __cplusplus
}
#endif

#endif //DIT_OngoingNOTIFICATION_H
