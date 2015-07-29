/*! @file	Notification.c
 *  @brief	Notification API가 정의되어있다.
 *  @note	Notification API가 정의되어있다.
 *  @see	Notification.h
*/


#include "Interface/Notification.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <notification.h>
#include <dlog.h>

const char * NotificationErrorCheck (int errCode);

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

bool NotificationShow (Notification this_gen)
{
    if ( this_gen != NULL)
    {

        NotificationExtend * this = (NotificationExtend *)this_gen;
        notification_error_e ret = NOTIFICATION_ERROR_NONE;

        ret = notification_post (this->notification_handle);
        if ( ret != NOTIFICATION_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", NotificationErrorCheck (ret));
            return false;
        }
        this->visible = true;
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool NotificationHide (Notification this_gen)
{
    if ( this_gen != NULL)
    {
        NotificationExtend * this = (NotificationExtend *)this_gen;
        notification_error_e ret = NOTIFICATION_ERROR_NONE;

        ret = notification_delete (this->notification_handle);
        if ( ret != NOTIFICATION_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", NotificationErrorCheck (ret));
            return false;
        }
        this->visible = false;
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool setNotificationTitle (Notification this_gen, String title)
{
    if ( this_gen != NULL)
    {
        NotificationExtend * this = (NotificationExtend *)this_gen;

        if ( NULL == title )
        {
            dlog_print (DLOG_INFO, "DIT", "NULL Title");
            return false;
        }

        if ( NULL != this->title )
        {
            free (this->title);
        }

        this->title = malloc (strlen (title) + sizeof (char));
        strcpy(this->title, title);
        notification_error_e ret = NOTIFICATION_ERROR_NONE;

        ret = notification_set_text (this->notification_handle, NOTIFICATION_TEXT_TYPE_TITLE, this->title, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
        if ( ret != NOTIFICATION_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", NotificationErrorCheck (ret));
            return false;
        }
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool setNotificationText (Notification this_gen, String text)
{
    if ( this_gen != NULL)
    {

        NotificationExtend * this = (NotificationExtend *)this_gen;

        if ( NULL == text )
        {
            dlog_print (DLOG_INFO, "DIT", "NULL Text");
            return false;
        }

        if ( NULL != this->text )
        {
            free (this->text);
        }

        this->text = malloc (strlen (text) + sizeof (char));
        strcpy(this->text, text);
        notification_error_e ret = NOTIFICATION_ERROR_NONE;
        ret = notification_set_text (this->notification_handle, NOTIFICATION_TEXT_TYPE_CONTENT, this->text, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
        if ( ret != NOTIFICATION_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", NotificationErrorCheck (ret));
            return false;
        }
        return true;

    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool setNotificationIcon (Notification this_gen, String imagePath)
{
    if ( this_gen != NULL)
    {
        NotificationExtend * this = (NotificationExtend *)this_gen;

        if ( NULL == imagePath )
        {
            dlog_print (DLOG_INFO, "DIT", "NULL iconpath");

            return false;
        }

        if ( NULL != this->imagePath )
        {
            free (this->imagePath);
        }

        this->imagePath = malloc (strlen (imagePath) + sizeof (char));
        strcpy(this->imagePath, imagePath);
        notification_error_e ret = NOTIFICATION_ERROR_NONE;
        ret = notification_set_image (this->notification_handle, NOTIFICATION_IMAGE_TYPE_ICON, this->imagePath);
        if ( ret != NOTIFICATION_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", NotificationErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool setNotificationSound (Notification this_gen, String soundPath)
{

    if ( this_gen != NULL)
    {

        NotificationExtend * this = (NotificationExtend *)this_gen;

        if ( NULL == soundPath )
        {
            dlog_print (DLOG_INFO, "DIT", "NULL soundpath");
            return false;
        }

        if ( NULL != this->soundPath )
        {
            free (this->soundPath);
        }

        this->soundPath = malloc (strlen (soundPath) + sizeof (char));
        strcpy(this->soundPath, soundPath);
        notification_error_e ret = NOTIFICATION_ERROR_NONE;
        ret = notification_set_sound (this->notification_handle, NOTIFICATION_SOUND_TYPE_USER_DATA, this->soundPath);
        if ( ret != NOTIFICATION_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", NotificationErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

bool updateNotification (Notification this_gen)
{
    if ( this_gen != NULL)
    {
        NotificationExtend * this = (NotificationExtend *)this_gen;
        notification_error_e ret = NOTIFICATION_ERROR_NONE;

        ret = notification_update (this->notification_handle);
        if ( ret != NOTIFICATION_ERROR_NONE )
        {
            dlog_print (DLOG_INFO, "DIT", "%s", NotificationErrorCheck (ret));
            return false;
        }
        return true;
    }
    dlog_print (DLOG_INFO, "DIT", "NULL module");
    return false;
}

const char * NotificationErrorCheck (int errCode)
{
    switch (errCode)
    {
    case NOTIFICATION_ERROR_NONE :
        return "NOTIFICATION_ERROR_NONE : Success";

    case NOTIFICATION_ERROR_INVALID_PARAMETER :
        return "NOTIFICATION_ERROR_INVALID_PARAMETER : Invalid parameter";

    case NOTIFICATION_ERROR_OUT_OF_MEMORY:
        return "NOTIFICATION_ERROR_OUT_OF_MEMORY : Out of memory";

    case NOTIFICATION_ERROR_IO_ERROR :
        return "NOTIFICATION_ERROR_IO_ERROR : I/O error";

    case NOTIFICATION_ERROR_PERMISSION_DENIED :
        return "NOTIFICATION_ERROR_PERMISSION_DENIED : Permission denied";

    case NOTIFICATION_ERROR_FROM_DB:
        return "NOTIFICATION_ERROR_FROM_DB : Error from DB query";

    case NOTIFICATION_ERROR_ALREADY_EXIST_ID:
        return "NOTIFICATION_ERROR_ALREADY_EXIST_ID : Already exist private ID";

    case NOTIFICATION_ERROR_FROM_DBUS :
        return "NOTIFICATION_ERROR_FROM_DBUS : Error from DBus";

    case NOTIFICATION_ERROR_NOT_EXIST_ID:
        return "NOTIFICATION_ERROR_NOT_EXIST_ID : Not exist private ID";

    case NOTIFICATION_ERROR_SERVICE_NOT_READY:
        return "NOTIFICATION_ERROR_SERVICE_NOT_READY : No response from notification service";

    default:
        return "NOTIFICATION_ERROR_UNKNOWN";
    }
}
