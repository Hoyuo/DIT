/*
 * OngoingNotification.c
 *
 *  Created on: Jun 22, 2015
 *      Author: parksanghyun
 *      Modifier: parkbeomchan
 */


#include <stdlib.h>
#include <string.h>
#include "Interface/OngoingNotification.h"

void setOngoingTitle(OngoingNotification* this_gen, char* title) {
    OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;
    if(NULL!=this->title)free(this->title);
    this->title = malloc(strlen(title)+sizeof(char));
     strcpy(this->title,title);
}

void setOngoingText(OngoingNotification* this_gen, char* text) {
    OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;
    if(NULL!=this->text)
    	free(this->text);
    this->text = malloc(strlen(text)+sizeof(char));
     strcpy(this->text,text);
}

void setOngoingIcon(OngoingNotification* this_gen, char* imagepath) {
    OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;
    if(NULL!=this->imagepath){
    	free(this->imagepath);
    }
    this->imagepath = malloc(strlen(imagepath)+sizeof(char));
     strcpy(this->imagepath,imagepath);
}


void showOngoing(OngoingNotification* this_gen) {
    OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;
    this->ongoingnotification_handle = notification_create(NOTIFICATION_TYPE_ONGOING);
    notification_set_property(this->ongoingnotification_handle, NOTIFICATION_PROP_DISABLE_TICKERNOTI);
    notification_set_image(this->ongoingnotification_handle, NOTIFICATION_IMAGE_TYPE_ICON, this->imagepath);
    notification_set_text(this->ongoingnotification_handle, NOTIFICATION_TEXT_TYPE_TITLE, this->title, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
    notification_set_text(this->ongoingnotification_handle, NOTIFICATION_TEXT_TYPE_CONTENT, this->text, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);

    notification_post(this->ongoingnotification_handle);
}


void hideOngoing(OngoingNotification* this_gen){
    OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;

	notification_delete(this->ongoingnotification_handle);
}


void deleteOngoingNotification(OngoingNotification* this_gen) {

    if (this_gen != NULL) {
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

        this_gen = NULL;
    }
}

OngoingNotification* newOngoingNotification() {
    OngoingNotificationExtend* this;

    this = (OngoingNotificationExtend*) malloc(sizeof(OngoingNotificationExtend));
    this->Ongoingnotification.showOngoingNotification = showOngoing;
    this->Ongoingnotification.hideOngoingNotification = hideOngoing;
    this->Ongoingnotification.setOngoingNotificationTitle = setOngoingTitle;
    this->Ongoingnotification.setOngoingNotificationText = setOngoingText;
    this->Ongoingnotification.setOngoingNotificationIcon = setOngoingIcon;
    this->title = NULL;
    this->text = NULL;
    this->imagepath = NULL;

    return &this->Ongoingnotification;
}

