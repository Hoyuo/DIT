/*
 * OngoingNotification.c
 *
 *  Created on: Jun 22, 2015
 *      Author: parksanghyun
 *      Modifier: parkbeomchan
 */


#include <stdlib.h>
#include "Interface/OngoingNotification.h"

void setOngoingNotificationTitle(OngoingNotification* this_gen, char* title) {
    OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;
    this->title = title;

}

void setOngoingNotificationText(OngoingNotification* this_gen, char* text) {
    OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;
    this->text = text;
}

void setOngoingNotificationIcon(OngoingNotification* this_gen, char* imagepath) {
    OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;
    this->imagepath = imagepath;

}


void createOngoingNotification(OngoingNotification* this_gen) {
	OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;
    this->ongoingnotification_handle = notification_create(NOTIFICATION_TYPE_ONGOING);
    notification_set_property(this->ongoingnotification_handle, NOTIFICATION_PROP_DISABLE_TICKERNOTI);
    notification_set_image(this->ongoingnotification_handle, NOTIFICATION_IMAGE_TYPE_ICON, this->imagepath);
    notification_set_text(this->ongoingnotification_handle, NOTIFICATION_TEXT_TYPE_TITLE, this->title, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
    notification_set_text(this->ongoingnotification_handle, NOTIFICATION_TEXT_TYPE_CONTENT, this->text, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);

    notification_post( this->ongoingnotification_handle);
}

void deleteOngoingNotification(OngoingNotification* this_gen) {

    if (this_gen != NULL) {
    	OngoingNotificationExtend* this = (OngoingNotificationExtend*) this_gen;

        notification_delete(this->ongoingnotification_handle);
        notification_free  (this->ongoingnotification_handle);
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

        this_gen=NULL;
    }
}

OngoingNotification* newOngoingNotification() {
    OngoingNotificationExtend* this;

    this = (OngoingNotificationExtend*) malloc(sizeof(OngoingNotificationExtend));
    this->Ongoingnotification.create = createOngoingNotification;
    this->Ongoingnotification.delete = deleteOngoingNotification;
    this->Ongoingnotification.setTitle = setOngoingNotificationTitle;
    this->Ongoingnotification.setText = setOngoingNotificationText;
    this->Ongoingnotification.setIcon = setOngoingNotificationIcon;
    this->title = NULL;
    this->text = NULL;
    this->imagepath = NULL;


    return &this->Ongoingnotification;
}

