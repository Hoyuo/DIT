/*
 * Notification.c
 *
 *  Created on: Jun 22, 2015
 *      Author: parksanghyun
 *
 */
#include "Interface/Notification.h"
#include <notification.h>
#include <stdlib.h>
#include <string.h>

void show(Notification* this_gen) {

    NotificationExtend* this = (NotificationExtend*) this_gen;
    this->notification_handle = notification_create(NOTIFICATION_TYPE_NOTI);

    notification_set_text(this->notification_handle, NOTIFICATION_TEXT_TYPE_TITLE, this->title, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
    notification_set_text(this->notification_handle, NOTIFICATION_TEXT_TYPE_CONTENT, this->text, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
    notification_set_image(this->notification_handle, NOTIFICATION_IMAGE_TYPE_ICON, this->imagepath);

    notification_post(this->notification_handle);
}

void hide(Notification* this_gen){
    NotificationExtend* this = (NotificationExtend*) this_gen;

    notification_delete(this->notification_handle);

}

void setTitle(Notification* this_gen, char* title) {

    NotificationExtend* this = (NotificationExtend*) this_gen;
    this->title = malloc(strlen(title)+sizeof(char));
    strcpy(this->title,title);

}

void setText(Notification* this_gen, char* text) {

    NotificationExtend* this = (NotificationExtend*) this_gen;
    this->text = malloc(strlen(text)+sizeof(char));
       strcpy(this->text,text);
}

void setIcon(Notification* this_gen, char* imagepath) {
    NotificationExtend* this = (NotificationExtend*) this_gen;
    this->imagepath = malloc(strlen(imagepath)+sizeof(char));
       strcpy(this->imagepath,imagepath);
}


//destroyer
void deleteNotification(Notification* this_gen) {

    if (this_gen != NULL) {
        NotificationExtend* this = (NotificationExtend*) this_gen;
        if (NULL != this->title) {
            free(this->title);
        }
        if (NULL != this->text) {
            free(this->text);
        }
        if (NULL != this->imagepath) {
            free(this->imagepath);
        }
        if (NULL != this->notification_handle) {
            notification_free(this->notification_handle);
        }
        free(this);

    }




}


Notification* newNotification() {
       NotificationExtend* this;

       this = (NotificationExtend*) malloc(sizeof(NotificationExtend));
       this->notification.showNotification= show;
       this->notification.hideNotification = hide;
       this->notification.setNotificationTitle= setTitle;
       this->notification.setNotificationText = setText;
       this->notification.setNotificationIcon = setIcon;
       this->title = NULL;
       this->text = NULL;
       this->imagepath = NULL;


       return &this->notification;
   }

