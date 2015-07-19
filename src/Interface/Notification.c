#include "Interface/Notification.h"

#include <stdlib.h>
#include <string.h>

#include <notification.h>

Notification NewNotification (void)
{
    NotificationExtend * this;

    this = (NotificationExtend *)malloc (sizeof (NotificationExtend));

    this->notification.Show     = NotificationShow;
    this->notification.Hide     = NotificationHide;
    this->notification.setTitle = setNotificationTitle;
    this->notification.setText  = setNotificationText;
    this->notification.setIcon  = setNotificationIcon;
    this->notification.setSound = setNotificationSound;
    this->notification.update   = updateNotification;

    this->notification_handle = notification_create (NOTIFICATION_TYPE_NOTI);
    this->title               = NULL;
    this->text                = NULL;
    this->imagePath           = NULL;
    this->soundPath           = NULL;
    this->visible             = false;

    return &this->notification;
}

void DestroyNotification (Notification this_gen)
{

    if ( this_gen != NULL)
    {
        NotificationExtend * this = (NotificationExtend *)this_gen;

        if ( NULL != this->title )
        {
            free (this->title);
        }

        if ( NULL != this->text )
        {
            free (this->text);
        }

        if ( NULL != this->imagePath )
        {
            free (this->imagePath);
        }

        if ( NULL != this->soundPath )
        {
            free (this->soundPath);
        }

        if ( this->visible )
        {
            notification_delete (this->notification_handle);
            this->visible = false;
        }

        if ( NULL != this->notification_handle )
        {
            notification_free (this->notification_handle);
        }

        free (this);
    }
}

void NotificationShow (Notification this_gen)
{
    if ( this_gen != NULL)
    {

        NotificationExtend * this = (NotificationExtend *)this_gen;

        notification_set_text (this->notification_handle, NOTIFICATION_TEXT_TYPE_TITLE, this->title, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
        notification_set_text (this->notification_handle, NOTIFICATION_TEXT_TYPE_CONTENT, this->text, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
        notification_set_image (this->notification_handle, NOTIFICATION_IMAGE_TYPE_ICON, this->imagePath);
        notification_set_sound (this->notification_handle, NOTIFICATION_SOUND_TYPE_USER_DATA, this->soundPath);

        notification_post (this->notification_handle);

        this->visible = true;
    }
}

void NotificationHide (Notification this_gen)
{
    if ( this_gen != NULL)
    {
        NotificationExtend * this = (NotificationExtend *)this_gen;

        notification_delete (this->notification_handle);

        this->visible = false;
    }
}

void setNotificationTitle (Notification this_gen, String title)
{
    if ( this_gen != NULL)
    {
        NotificationExtend * this = (NotificationExtend *)this_gen;

        if ( NULL == title )
        {
            return;
        }

        if ( NULL != this->title )
        {
            free (this->title);
        }

        this->title = malloc (strlen (title) + sizeof (char));
        strcpy(this->title, title);
    }
}

void setNotificationText (Notification this_gen, String text)
{
    if ( this_gen != NULL)
    {

        NotificationExtend * this = (NotificationExtend *)this_gen;

        if ( NULL == text )
        {
            return;
        }

        if ( NULL != this->text )
        {
            free (this->text);
        }

        this->text = malloc (strlen (text) + sizeof (char));
        strcpy(this->text, text);
    }
}

void setNotificationIcon (Notification this_gen, String imagePath)
{
    if ( this_gen != NULL)
    {
        NotificationExtend * this = (NotificationExtend *)this_gen;

        if ( NULL == imagePath )
        {
            return;
        }

        if ( NULL != this->imagePath )
        {
            free (this->imagePath);
        }

        this->imagePath = malloc (strlen (imagePath) + sizeof (char));
        strcpy(this->imagePath, imagePath);
    }
}

void setNotificationSound (Notification this_gen, String soundPath)
{

    if ( this_gen != NULL)
    {

        NotificationExtend * this = (NotificationExtend *)this_gen;

        if ( NULL == soundPath )
        {
            return;
        }

        if ( NULL != this->soundPath )
        {
            free (this->soundPath);
        }

        this->soundPath = malloc (strlen (soundPath) + sizeof (char));
        strcpy(this->soundPath, soundPath);
    }
}

void updateNotification (Notification this_gen)
{
    if ( this_gen != NULL)
    {
        NotificationExtend * this = (NotificationExtend *)this_gen;

        notification_set_text (this->notification_handle, NOTIFICATION_TEXT_TYPE_TITLE, this->title, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
        notification_set_text (this->notification_handle, NOTIFICATION_TEXT_TYPE_CONTENT, this->text, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
        notification_set_image (this->notification_handle, NOTIFICATION_IMAGE_TYPE_ICON, this->imagePath);
        notification_set_sound (this->notification_handle, NOTIFICATION_SOUND_TYPE_USER_DATA, this->soundPath);

        notification_update (this->notification_handle);
    }
}

const char * NotificationErrorCheck (int errCode)
{
    switch (errCode)
    {
    case NOTIFICATION_ERROR_NONE :
        return "NOTIFICATION_ERROR_NONE : Success";

    case NOTIFICATION_ERROR_INVALID_PARAMETER :
        return " NOTIFICATION_ERROR_INVALID_PARAMETER : Invalid parameter";

    case NOTIFICATION_ERROR_OUT_OF_MEMORY:
        return "NOTIFICATION_ERROR_OUT_OF_MEMORY : out of memory";

    case NOTIFICATION_ERROR_IO_ERROR :
        return "NOTIFICATION_ERROR_IO_ERROR : I/O error";

    case NOTIFICATION_ERROR_PERMISSION_DENIED :
        return "NOTIFICATION_ERROR_PERMISSION_DENIED : Permission denied";

    case NOTIFICATION_ERROR_FROM_DB:
        return "NOTIFICATION_ERROR_FROM_DB : Error from DB query";

    case NOTIFICATION_ERROR_ALREADY_EXIST_ID:
        return "NOTIFICATION_ERROR_ALREADY_EXIST_ID : Already exist private ID";

    case NOTIFICATION_ERROR_FROM_DBUS :
        return "NOTIFICATION_ERROR_FROM_DBUS Error from DBus";

    case NOTIFICATION_ERROR_NOT_EXIST_ID:
        return "NOTIFICATION_ERROR_NOT_EXIST_ID Not exist private ID";

    case NOTIFICATION_ERROR_SERVICE_NOT_READY:
        return "NOTIFICATION_ERROR_SERVICE_NOT_READY : No reponse from notification service";

    default:
        return "NOTIFICATION_ERROR_UNKOWN";
    }
}
