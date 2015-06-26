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
	 if (this_gen == NULL)
	    	return;
    NotificationExtend* this = (NotificationExtend*) this_gen;
    this->notification_handle = notification_create(NOTIFICATION_TYPE_NOTI);

    notification_set_text(this->notification_handle, NOTIFICATION_TEXT_TYPE_TITLE, this->title, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
    notification_set_text(this->notification_handle, NOTIFICATION_TEXT_TYPE_CONTENT, this->text, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
    notification_set_image(this->notification_handle, NOTIFICATION_IMAGE_TYPE_ICON, this->imagepath);

    notification_post(this->notification_handle);
}

void hide(Notification* this_gen){
	 if (this_gen == NULL)
	    	return;
    NotificationExtend* this = (NotificationExtend*) this_gen;

    notification_delete(this->notification_handle);

}

void setTitle(Notification* this_gen, char* title) {
	 if (this_gen == NULL)
	    	return;
    NotificationExtend* this = (NotificationExtend*) this_gen;

    if(NULL==title){
	   	return;
	 }
	 if(NULL!=this->title){
	 free(this->title);
  	    }
	 this->title = malloc(strlen(title)+sizeof(char));
	 strcpy(this->title,title);
}

void setText(Notification* this_gen, char* text) {
	 if (this_gen == NULL)
	    	return;

    NotificationExtend* this = (NotificationExtend*) this_gen;
    if(NULL==text){
    	return;
    }
    if(NULL!=this->text){
    	free(this->text);
    }
    this->text = malloc(strlen(text)+sizeof(char));
          strcpy(this->text,text);
}

void setIcon(Notification* this_gen, char* imagepath) {
	 if (this_gen == NULL)
	    	return;
    NotificationExtend* this = (NotificationExtend*) this_gen;
    if(NULL==imagepath){
       	return;
       }
       if(NULL!=this->imagepath){
    	   free(this->imagepath);
       }
    this->imagepath = malloc(strlen(imagepath)+sizeof(char));
       strcpy(this->imagepath,imagepath);

}


//destroyer
void DestroyNotification(Notification* this_gen) {

	 if (this_gen == NULL)
	    	return;

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


Notification* NewNotification() {
       NotificationExtend* this;

       this = (NotificationExtend*) malloc(sizeof(NotificationExtend));
       this->notification.ShowNotification= show;
       this->notification.HideNotification = hide;
       this->notification.SetNotificationTitle= setTitle;
       this->notification.SetNotificationText = setText;
       this->notification.SetNotificationIcon = setIcon;
       this->title = NULL;
       this->text = NULL;
       this->imagepath = NULL;


       return &this->notification;
   }

