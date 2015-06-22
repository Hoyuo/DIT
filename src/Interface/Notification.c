/*
 * Notification.c
 *
 *  Created on: Jun 22, 2015
 *      Author: parksanghyun
 *
 */
#include "Interface/Notification.h"
#include <stdlib.h>

void createNotification(Notification* this_gen){

    NotificationExtend* this = (NotificationExtend *)this_gen;
    this->notification_handle = notification_create(NOTIFICATION_TYPE_NOTI);

    notification_set_text(this->notification_handle,NOTIFICATION_TYPE_TITLE,this->title,This,);
}

void setNotificationTitle(Notification* this_gen,char* title){

    NotificationExtend* this = (NotificationExtend *)this_gen;
    this->text="Title";

}

void setNotificationText(Notification* this_gen,char* text){
    this->text="Text";

}

void setNotificationIcon(Notification* this_gen,char* imagePath){
    NotificationExtend* this = (NotificationExtend*) this_gen;

}


void deleteNotification(Notification* this_gen){

    if(this_gen != NULL) {
        NotificationExtend* this = (NotificationExtend*) this_gen;
        if(NULL!=this->title)
            free(this->title);
        if(NULL!=this->text)
            free(this->text);
        if(NULL!=this->imagePath)
            free(this->imagePath);
        if(NULL!=this->notification_handle)
            notification_free(this->notification_handle);
        free(this);

    }
}

Notification* newNotification(){
    NotificationExtend *this;

    this = (NotificationExtend*) malloc(sizeof(NotificationExtend));
    this->notification.create= createNotification;
    this->notification.delete= deleteNotification;
    this->notification.setTitle=setNotificationTitle;
    this->notification.setText=setNotificationText;
    this->notification.setIcon=setNotificationIcon;
    this->title=NULL;
    this->text=NULL;
    this->imagePath=NULL;


    return &this->notification;
}


