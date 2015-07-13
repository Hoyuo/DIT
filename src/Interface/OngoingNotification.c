#include "Interface/OngoingNotification.h"
#include <stdlib.h>
#include <string.h>

void setOngoingTitle(OngoingNotification* this_gen, char* title) {
    if (this_gen == NULL) {
        return;
    }
    OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;
    if (NULL == title) {
        return;
    }
    if (NULL != this->title) {
        free(this->title);
    }
    this->title = malloc(strlen(title) + sizeof(char));
    strcpy(this->title, title);
}

void setOngoingText(OngoingNotification* this_gen, char* text) {
    if (this_gen == NULL) {
        return;
    }
    OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;
    if (NULL == text) {
        return;
    }
    if (NULL != this->text) {
        free(this->text);
    }
    this->text = malloc(strlen(text) + sizeof(char));
    strcpy(this->text, text);
}

void setOngoingIcon(OngoingNotification* this_gen, char* imagepath) {
    if (this_gen == NULL) {
        return;
    }
    OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;
    if (NULL == imagepath) {
        return;
    }
    if (NULL != this->imagepath) {
        free(this->imagepath);
    }
    this->imagepath = malloc(strlen(imagepath) + sizeof(char));
    strcpy(this->imagepath, imagepath);
}


void showOngoing(OngoingNotification* this_gen) {
    if (this_gen == NULL) {
        return;
    }
    OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;
   notification_set_image(this->ongoingnotification_handle, NOTIFICATION_IMAGE_TYPE_ICON, this->imagepath);
    notification_set_text(this->ongoingnotification_handle, NOTIFICATION_TEXT_TYPE_TITLE, this->title, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
    notification_set_text(this->ongoingnotification_handle, NOTIFICATION_TEXT_TYPE_CONTENT, this->text, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);

    notification_post(this->ongoingnotification_handle);
}


void hideOngoing(OngoingNotification* this_gen) {
    if (this_gen == NULL) {
        return;
    }
    OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;

    notification_delete(this->ongoingnotification_handle);
}

void setOngoingProgress(OngoingNotification* this_gen,double progress){

    OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;

    notification_set_progress(this->ongoingnotification_handle,progress);
}

void updateOngoiongNoti(OngoingNotification* this_gen){

    OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;

    notification_update(this->ongoingnotification_handle);
}



void DestroyOngoingNotification(OngoingNotification* this_gen) {

    if (this_gen == NULL) {
        return;
    }
    OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;

    notification_delete(this->ongoingnotification_handle);
    notification_free(this->ongoingnotification_handle);
    if (NULL != this->title) {
        free(this->title);
    }
    if (NULL != this->text) {
        free(this->text);
    }
    if (NULL != this->imagepath) {
        free(this->imagepath);
    }

    free(this);


}

OngoingNotification* NewOngoingNotification() {
    OngoingNotificationExtend* this;

    this = (OngoingNotificationExtend*) malloc(sizeof(OngoingNotificationExtend));
    this->Ongoingnotification.ShowOngoingNotification = showOngoing;
    this->Ongoingnotification.HideOngoingNotification = hideOngoing;
    this->Ongoingnotification.SetOngoingNotificationTitle = setOngoingTitle;
    this->Ongoingnotification.SetOngoingNotificationText = setOngoingText;
    this->Ongoingnotification.SetOngoingNotificationIcon = setOngoingIcon;
    this->Ongoingnotification.SetOngoingNotificationProgress = setOngoingProgress;
    this->Ongoingnotification.updateOngoiongNotification = updateOngoiongNoti;

    this->title = NULL;
    this->text = NULL;
    this->imagepath = NULL;

    this->ongoingnotification_handle = notification_create(NOTIFICATION_TYPE_ONGOING);
    notification_set_display_applist(this->ongoingnotification_handle, NOTIFICATION_DISPLAY_APP_NOTIFICATION_TRAY | NOTIFICATION_DISPLAY_APP_TICKER);

    return &this->Ongoingnotification;
}

